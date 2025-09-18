# Hướng Dẫn Demo Tích Hợp Apache Doris với Power BI cho Dự Án Data Mining

## Tổng Quan Dự Án

Dự án này tập trung vào việc ứng dụng các thuật toán khai thác dữ liệu (K-Means Clustering và Naive Bayes Classification) để dự báo phân bổ hàng hóa bán lẻ, với việc tích hợp Apache Doris làm data warehouse và Power BI cho trực quan hóa dữ liệu.

## Quy Trình Demo Thực Tế

### Bước 1: Thiết Lập Database và Nạp Dữ Liệu Ban Đầu
### Bước 2: Kết Nối Spark với Doris và Tạo Bảng
### Bước 3: Chạy Data Mining và Nạp Kết Quả vào Doris
### Bước 4: Tạo SQL Queries và Biểu Đồ Power BI
### Bước 5: Tích Hợp Hoàn Chỉnh Dashboard

---

## Bước 1: Thiết Lập Database và Nạp Dữ Liệu Ban Đầu

### 1.1. Tạo Database và Bảng Sales Duy Nhất

```sql
-- Kết nối đến Apache Doris
mysql -h localhost -P 9030 -u root -p

-- Tạo database retail_db
CREATE DATABASE IF NOT EXISTS retail_db;
USE retail_db;

-- Tạo bảng sales duy nhất với cấu trúc phù hợp cho CSV
CREATE TABLE IF NOT EXISTS sales (
    `date` DATE NOT NULL COMMENT "Ngày bán hàng",
    `store_id` VARCHAR(50) NOT NULL COMMENT "ID cửa hàng",
    `product_id` VARCHAR(50) NOT NULL COMMENT "ID sản phẩm",
    `category` VARCHAR(100) NOT NULL COMMENT "Danh mục sản phẩm",
    `region` VARCHAR(50) NOT NULL COMMENT "Khu vực",
    `inventory_level` INT NOT NULL COMMENT "Mức tồn kho",
    `units_sold` INT NOT NULL COMMENT "Số lượng bán",
    `units_ordered` INT NOT NULL COMMENT "Số lượng đặt hàng",
    `demand_forecast` DOUBLE NOT NULL COMMENT "Dự báo nhu cầu",
    `price` DOUBLE NOT NULL COMMENT "Giá bán",
    `discount` INT NOT NULL COMMENT "Mức giảm giá (%)",
    `weather_condition` VARCHAR(50) NOT NULL COMMENT "Điều kiện thời tiết",
    `holiday_promotion` TINYINT NOT NULL COMMENT "Khuyến mãi/Lễ hội (0/1)",
    `competitor_pricing` DOUBLE NOT NULL COMMENT "Giá đối thủ",
    `seasonality` VARCHAR(50) NOT NULL COMMENT "Mùa trong năm"
)
DUPLICATE KEY(`date`, `store_id`, `product_id`)
DISTRIBUTED BY HASH(`store_id`) BUCKETS 10
PROPERTIES (
    "replication_allocation" = "tag.location.default: 1",
    "storage_format" = "V2"
);
```

### 1.2. Nạp Dữ Liệu Ban Đầu từ CSV

```python
# import_initial_data.py
import pandas as pd
import mysql.connector
from mysql.connector import Error

def import_csv_to_doris():
    try:
        # Đọc CSV file
        print("Đang đọc file CSV...")
        df = pd.read_csv('retail_store_inventory.csv')
        
        # Kiểm tra dữ liệu
        print(f"Số dòng dữ liệu: {len(df)}")
        print(f"Các cột: {list(df.columns)}")
        print(f"Dữ liệu null trong cột Date: {df['Date'].isnull().sum()}")
        
        # Làm sạch dữ liệu
        df = df.dropna(subset=['Date'])  # Xóa dòng có Date null
        df['Date'] = pd.to_datetime(df['Date'])  # Chuyển đổi sang datetime
        
        # Kết nối đến Doris
        connection = mysql.connector.connect(
            host='localhost',
            port=9030,
            database='retail_db',
            user='root',
            password='password'
        )
        
        cursor = connection.cursor()
        
        # Chuẩn bị dữ liệu để insert
        insert_query = """
        INSERT INTO sales 
        (date, store_id, product_id, category, region, inventory_level, 
         units_sold, units_ordered, demand_forecast, price, discount, 
         weather_condition, holiday_promotion, competitor_pricing, seasonality)
        VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)
        """
        
        # Insert từng batch
        batch_size = 1000
        for i in range(0, len(df), batch_size):
            batch_df = df.iloc[i:i+batch_size]
            data_to_insert = []
            
            for _, row in batch_df.iterrows():
                data_to_insert.append((
                    row['Date'].strftime('%Y-%m-%d'),
                    row['Store ID'],
                    row['Product ID'],
                    row['Category'],
                    row['Region'],
                    int(row['Inventory Level']),
                    int(row['Units Sold']),
                    int(row['Units Ordered']),
                    float(row['Demand Forecast']),
                    float(row['Price']),
                    int(row['Discount']),
                    row['Weather Condition'],
                    int(row['Holiday/Promotion']),
                    float(row['Competitor Pricing']),
                    row['Seasonality']
                ))
            
            cursor.executemany(insert_query, data_to_insert)
            connection.commit()
            print(f"Đã import {min(i + batch_size, len(df))}/{len(df)} dòng")
        
        print("Import dữ liệu ban đầu thành công!")
        
    except Error as e:
        print(f"Lỗi: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    import_csv_to_doris()
```

```bash
# Chạy script import dữ liệu ban đầu
python import_initial_data.py
```

### 1.3. Kiểm Tra Dữ Liệu Ban Đầu

```sql
-- Kiểm tra số lượng dòng đã import
SELECT COUNT(*) as total_records FROM sales;

-- Kiểm tra dữ liệu mẫu
SELECT * FROM sales LIMIT 5;

-- Kiểm tra phân bố theo khu vực
SELECT region, COUNT(*) as store_count, SUM(units_sold) as total_sales
FROM sales 
GROUP BY region 
ORDER BY total_sales DESC;
```

---

## Bước 2: Kết Nối Spark với Doris và Tạo Bảng

### 2.1. Cấu Hình Spark trong WSL Ubuntu 22.04

```bash
# Trong WSL Ubuntu 22.04, cấu hình Spark
export SPARK_HOME=/opt/spark
export PATH=$PATH:$SPARK_HOME/bin:$SPARK_HOME/sbin

# Tạo file cấu hình Spark
cat > $SPARK_HOME/conf/spark-defaults.conf << EOF
spark.sql.adaptive.enabled=true
spark.sql.adaptive.coalescePartitions.enabled=true
spark.serializer=org.apache.spark.serializer.KryoSerializer
spark.sql.execution.arrow.pyspark.enabled=true
EOF
```

### 2.2. Cài Đặt MySQL Connector cho Spark

```bash
# Tải MySQL Connector
wget https://repo1.maven.org/maven2/mysql/mysql-connector-java/8.0.33/mysql-connector-java-8.0.33.jar

# Copy vào thư mục jars của Spark
sudo cp mysql-connector-java-8.0.33.jar $SPARK_HOME/jars/
```

### 2.3. Script Python để Kết Nối Spark-Doris và Tạo Bảng

```python
# spark_doris_setup.py
from pyspark.sql import SparkSession
from pyspark.sql.functions import *

def setup_spark_doris():
    # Khởi tạo Spark Session
    spark = SparkSession.builder \
        .appName("DorisSetup") \
        .config("spark.jars", "/opt/spark/jars/mysql-connector-java-8.0.33.jar") \
        .getOrCreate()
    
    try:
        # Kết nối đến Doris và đọc dữ liệu từ bảng sales
        print("Kết nối đến Doris và đọc dữ liệu...")
        doris_df = spark.read \
            .format("jdbc") \
            .option("url", "jdbc:mysql://localhost:9030/retail_db") \
            .option("dbtable", "sales") \
            .option("user", "root") \
            .option("password", "password") \
            .load()
        
        # Hiển thị thông tin dữ liệu
        print("Thông tin dữ liệu từ Doris:")
        doris_df.show(5)
        doris_df.printSchema()
        print(f"Tổng số dòng: {doris_df.count()}")
        
        # Tạo bảng product_clusters trong Doris
        print("Tạo bảng product_clusters...")
        create_clusters_table_sql = """
        CREATE TABLE IF NOT EXISTS product_clusters (
            `product_id` VARCHAR(50) NOT NULL COMMENT "ID sản phẩm",
            `cluster_id` INT NOT NULL COMMENT "ID cụm",
            `demand_score` DOUBLE NOT NULL COMMENT "Điểm nhu cầu",
            `price_score` DOUBLE NOT NULL COMMENT "Điểm giá cả",
            `discount_score` DOUBLE NOT NULL COMMENT "Điểm giảm giá",
            `competitor_price_score` DOUBLE NOT NULL COMMENT "Điểm giá đối thủ",
            `cluster_strategy` VARCHAR(100) NOT NULL COMMENT "Chiến lược cụm",
            `created_date` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT "Ngày tạo"
        )
        DUPLICATE KEY(`product_id`)
        DISTRIBUTED BY HASH(`product_id`) BUCKETS 5
        PROPERTIES (
            "replication_allocation" = "tag.location.default: 1"
        )
        """
        
        # Tạo bảng sales_predictions trong Doris
        print("Tạo bảng sales_predictions...")
        create_predictions_table_sql = """
        CREATE TABLE IF NOT EXISTS sales_predictions (
            `product_id` VARCHAR(50) NOT NULL COMMENT "ID sản phẩm",
            `store_id` VARCHAR(50) NOT NULL COMMENT "ID cửa hàng",
            `date` DATE NOT NULL COMMENT "Ngày dự báo",
            `predicted_high_sales` TINYINT NOT NULL COMMENT "Dự báo bán chạy (0/1)",
            `prediction_probability` DOUBLE NOT NULL COMMENT "Xác suất dự báo",
            `actual_sales` INT COMMENT "Doanh số thực tế",
            `prediction_accuracy` DOUBLE COMMENT "Độ chính xác dự báo",
            `created_date` DATETIME DEFAULT CURRENT_TIMESTAMP COMMENT "Ngày tạo"
        )
        DUPLICATE KEY(`product_id`, `store_id`, `date`)
        DISTRIBUTED BY HASH(`product_id`) BUCKETS 5
        PROPERTIES (
            "replication_allocation" = "tag.location.default: 1"
        )
        """
        
        # Thực hiện một số phép tính để test kết nối
        print("Thực hiện phép tính test...")
        summary_df = doris_df.groupBy("region", "category") \
            .agg(
                sum("units_sold").alias("total_sales"),
                avg("price").alias("avg_price"),
                count("*").alias("record_count")
            )
        
        summary_df.show()
        
        print("Kết nối Spark-Doris thành công!")
        print("Các bảng đã được tạo:")
        print("- product_clusters: Lưu trữ kết quả K-Means clustering")
        print("- sales_predictions: Lưu trữ kết quả Naive Bayes classification")
        
    except Exception as e:
        print(f"Lỗi: {e}")
    finally:
        spark.stop()

if __name__ == "__main__":
    setup_spark_doris()
```

### 2.4. Chạy Script Spark

```bash
# Chạy script Python để setup Spark-Doris
spark-submit \
  --master local[4] \
  --driver-memory 2g \
  --executor-memory 2g \
  spark_doris_setup.py
```

### 2.5. Kiểm Tra Kết Quả

```sql
-- Kiểm tra các bảng đã được tạo
SHOW TABLES;

-- Kiểm tra cấu trúc bảng product_clusters
DESC product_clusters;

-- Kiểm tra cấu trúc bảng sales_predictions
DESC sales_predictions;
```

---

## Bước 3: Chạy Data Mining và Nạp Kết Quả vào Doris

### 3.1. Chạy Notebook Data Mining

```bash
# Chạy notebook data mining để tạo kết quả K-Means và Naive Bayes
jupyter notebook Nhom12_DoAnKhaiThacDuLieu.ipynb
```

**Lưu ý**: Trong notebook, bạn cần lưu kết quả vào các biến:
- `df_with_clusters`: DataFrame chứa kết quả K-Means clustering
- `predictions_df`: DataFrame chứa kết quả Naive Bayes classification

### 3.2. Script Xuất Kết Quả Data Mining vào Doris

```python
# export_ml_results.py
import pandas as pd
import mysql.connector
from mysql.connector import Error

def export_to_doris():
    try:
        # Kết nối đến Doris
        connection = mysql.connector.connect(
            host='localhost',
            port=9030,
            database='retail_db',
            user='root',
            password='password'
        )
        
        cursor = connection.cursor()
        
        # 1. Xuất kết quả K-Means Clustering
        print("Đang xuất kết quả K-Means Clustering...")
        
        # Tạo DataFrame từ kết quả clustering (giả sử từ notebook)
        # Bạn cần thay thế bằng dữ liệu thực tế từ notebook
        cluster_data = []
        for idx, row in df_with_clusters.iterrows():
            cluster_data.append({
                'product_id': row['Product ID'],
                'cluster_id': row['Cluster'],
                'demand_score': row['Demand'],
                'price_score': row['Price'],
                'discount_score': row['Discount'],
                'competitor_price_score': row['Competitor Price'],
                'cluster_strategy': get_cluster_strategy(row['Cluster'])
            })
        
        cluster_df = pd.DataFrame(cluster_data)
        
        # Insert vào bảng product_clusters
        for _, row in cluster_df.iterrows():
            insert_query = """
            INSERT INTO product_clusters 
            (product_id, cluster_id, demand_score, price_score, discount_score, 
             competitor_price_score, cluster_strategy)
            VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            cursor.execute(insert_query, tuple(row))
        
        # 2. Xuất kết quả Naive Bayes Classification
        print("Đang xuất kết quả Naive Bayes Classification...")
        
        # Tạo DataFrame từ kết quả predictions (giả sử từ notebook)
        # Bạn cần thay thế bằng dữ liệu thực tế từ notebook
        prediction_data = []
        for idx, row in predictions_df.iterrows():
            prediction_data.append({
                'product_id': row['Product ID'],
                'store_id': row['Store ID'],
                'date': row['Date'],
                'predicted_high_sales': row['Predicted_High_Sales'],
                'prediction_probability': row['Prediction_Probability'],
                'actual_sales': row['Actual_Sales'],
                'prediction_accuracy': row['Prediction_Accuracy']
            })
        
        prediction_df = pd.DataFrame(prediction_data)
        
        # Insert vào bảng sales_predictions
        for _, row in prediction_df.iterrows():
            insert_query = """
            INSERT INTO sales_predictions 
            (product_id, store_id, date, predicted_high_sales, prediction_probability,
             actual_sales, prediction_accuracy)
            VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            cursor.execute(insert_query, tuple(row))
        
        connection.commit()
        print("Xuất dữ liệu ML thành công!")
        
    except Error as e:
        print(f"Lỗi kết nối: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

def get_cluster_strategy(cluster_id):
    """Xác định chiến lược dựa trên cluster ID"""
    strategies = {
        0: 'Budget Competitive',
        1: 'Premium High Demand', 
        2: 'Balanced Strategy',
        3: 'Premium Low Competition',
        4: 'Competitive Advantage'
    }
    return strategies.get(cluster_id, 'Unknown Strategy')

# Chạy hàm export
if __name__ == "__main__":
    export_to_doris()
```

### 3.3. Kiểm Tra Kết Quả Data Mining

```sql
-- Kiểm tra kết quả K-Means clustering
SELECT 
    cluster_id,
    cluster_strategy,
    COUNT(*) as product_count,
    AVG(demand_score) as avg_demand,
    AVG(price_score) as avg_price
FROM product_clusters 
GROUP BY cluster_id, cluster_strategy
ORDER BY cluster_id;

-- Kiểm tra kết quả Naive Bayes classification
SELECT 
    predicted_high_sales,
    COUNT(*) as prediction_count,
    AVG(prediction_probability) as avg_probability,
    AVG(prediction_accuracy) as avg_accuracy
FROM sales_predictions 
GROUP BY predicted_high_sales;
```

---

## Bước 4: Tạo SQL Queries và Biểu Đồ Power BI

### 4.1. Tạo Views Tích Hợp cho Power BI

```sql
-- View tổng hợp dữ liệu sales với kết quả clustering
CREATE VIEW sales_with_clusters AS
SELECT 
    s.*,
    pc.cluster_id,
    pc.cluster_strategy,
    pc.demand_score,
    pc.price_score,
    pc.discount_score,
    pc.competitor_price_score
FROM sales s
LEFT JOIN product_clusters pc ON s.product_id = pc.product_id;

-- View tổng hợp dữ liệu sales với predictions
CREATE VIEW sales_with_predictions AS
SELECT 
    s.*,
    sp.predicted_high_sales,
    sp.prediction_probability,
    sp.prediction_accuracy,
    CASE 
        WHEN sp.predicted_high_sales = 1 AND sp.prediction_probability > 0.8 THEN 'High Priority'
        WHEN sp.predicted_high_sales = 1 AND sp.prediction_probability > 0.6 THEN 'Medium Priority'
        WHEN sp.predicted_high_sales = 0 THEN 'Low Priority'
        ELSE 'Unknown'
    END as priority_level
FROM sales s
LEFT JOIN sales_predictions sp ON s.product_id = sp.product_id AND s.store_id = sp.store_id;

-- View dashboard tổng hợp
CREATE VIEW ml_dashboard AS
SELECT 
    s.region,
    s.category,
    s.store_id,
    s.product_id,
    s.units_sold,
    s.price,
    s.inventory_level,
    pc.cluster_strategy,
    sp.predicted_high_sales,
    sp.prediction_probability,
    sp.priority_level,
    CASE 
        WHEN pc.cluster_strategy = 'Premium High Demand' THEN 'Tăng tồn kho 30%'
        WHEN pc.cluster_strategy = 'Budget Competitive' THEN 'Tăng tồn kho 20%'
        WHEN sp.predicted_high_sales = 1 THEN 'Tăng tồn kho 25%'
        ELSE 'Giữ nguyên tồn kho'
    END as recommended_action
FROM sales s
LEFT JOIN product_clusters pc ON s.product_id = pc.product_id
LEFT JOIN sales_with_predictions sp ON s.product_id = sp.product_id AND s.store_id = sp.store_id;
```

### 4.2. 5 Câu SQL Queries Cho Power BI

#### 4.2.1. Phân Tích Doanh Số Theo Khu Vực và Danh Mục

```sql
-- Câu lệnh 1: Doanh số bán hàng theo khu vực và danh mục sản phẩm
SELECT 
    region,
    category,
    COUNT(*) as total_records,
    SUM(units_sold) as total_sales,
    AVG(units_sold) as avg_sales_per_day,
    SUM(units_sold * price) as total_revenue,
    AVG(price) as avg_price
FROM sales 
GROUP BY region, category
ORDER BY total_sales DESC;
```

**Mục đích**: Tạo biểu đồ cột kép (Dual Axis Chart) để so sánh doanh số và doanh thu theo khu vực và danh mục.

### 2.2. Phân Tích Xu Hướng Theo Thời Gian

```sql
-- Câu lệnh 2: Xu hướng doanh số theo tháng và mùa
SELECT 
    YEAR(date) as year,
    MONTH(date) as month,
    seasonality,
    SUM(units_sold) as monthly_sales,
    AVG(inventory_level) as avg_inventory,
    SUM(CASE WHEN holiday_promotion = 1 THEN units_sold ELSE 0 END) as promotional_sales,
    COUNT(DISTINCT store_id) as active_stores
FROM sales 
GROUP BY YEAR(date), MONTH(date), seasonality
ORDER BY year, month;
```

**Mục đích**: Tạo biểu đồ đường (Line Chart) và biểu đồ vùng (Area Chart) để hiển thị xu hướng theo thời gian.

### 2.3. Phân Tích Hiệu Quả Khuyến Mãi

```sql
-- Câu lệnh 3: Tác động của khuyến mãi và thời tiết đến doanh số
SELECT 
    holiday_promotion,
    weather_condition,
    AVG(units_sold) as avg_sales,
    AVG(discount) as avg_discount,
    AVG(price) as avg_price,
    COUNT(*) as record_count,
    SUM(units_sold) as total_sales
FROM sales 
GROUP BY holiday_promotion, weather_condition
ORDER BY total_sales DESC;
```

**Mục đích**: Tạo biểu đồ nhiệt (Heatmap) và biểu đồ tròn (Pie Chart) để phân tích tác động của các yếu tố bên ngoài.

### 2.4. Phân Tích Cạnh Tranh Giá

```sql
-- Câu lệnh 4: Phân tích giá cả và cạnh tranh
SELECT 
    category,
    AVG(price) as avg_our_price,
    AVG(competitor_pricing) as avg_competitor_price,
    AVG(price - competitor_pricing) as price_difference,
    CASE 
        WHEN AVG(price) < AVG(competitor_pricing) THEN 'Competitive Advantage'
        WHEN AVG(price) > AVG(competitor_pricing) THEN 'Premium Pricing'
        ELSE 'Market Parity'
    END as pricing_strategy,
    AVG(units_sold) as avg_sales
FROM sales 
GROUP BY category
ORDER BY price_difference DESC;
```

**Mục đích**: Tạo biểu đồ thanh ngang (Horizontal Bar Chart) và biểu đồ scatter để so sánh giá cả.

### 2.5. Phân Tích Tồn Kho và Dự Báo Nhu Cầu

```sql
-- Câu lệnh 5: Phân tích tồn kho và độ chính xác dự báo
SELECT 
    store_id,
    category,
    AVG(inventory_level) as avg_inventory,
    AVG(units_sold) as avg_sales,
    AVG(demand_forecast) as avg_forecast,
    AVG(ABS(units_sold - demand_forecast)) as forecast_error,
    AVG(inventory_level - units_sold) as inventory_excess,
    CASE 
        WHEN AVG(inventory_level - units_sold) > 50 THEN 'Overstocked'
        WHEN AVG(inventory_level - units_sold) < -20 THEN 'Understocked'
        ELSE 'Optimal'
    END as inventory_status
FROM sales 
GROUP BY store_id, category
HAVING COUNT(*) > 10  -- Chỉ lấy các cửa hàng có đủ dữ liệu
ORDER BY forecast_error DESC;
```

**Mục đích**: Tạo biểu đồ bubble chart và biểu đồ gauge để hiển thị tình trạng tồn kho.

---

## Bước 3: Tạo Biểu Đồ trên Power BI

### 3.1. Kết Nối Apache Doris với Power BI

1. **Cài đặt Driver**:
   - Tải và cài đặt MySQL ODBC Driver
   - Cấu hình connection string đến Apache Doris

2. **Tạo Connection**:
   ```
   Server: [Doris_FE_Host]:[Query_Port]
   Database: [Database_Name]
   Username: [Username]
   Password: [Password]
   ```

### 2.2. Tạo Các Biểu Đồ Từ SQL Queries

#### Biểu Đồ 1: Doanh Số Theo Khu Vực và Danh Mục
- **Loại**: Clustered Column Chart
- **Trục X**: Region
- **Trục Y**: Total_Sales
- **Legend**: Category
- **Cách tạo**:
  1. Import query 1 vào Power BI
  2. Kéo Region vào Axis
  3. Kéo Total_Sales vào Values
  4. Kéo Category vào Legend

#### Biểu Đồ 2: Xu Hướng Theo Thời Gian
- **Loại**: Line Chart
- **Trục X**: Month
- **Trục Y**: Monthly_Sales
- **Legend**: Seasonality
- **Cách tạo**:
  1. Import query 2 vào Power BI
  2. Kéo Month vào Axis
  3. Kéo Monthly_Sales vào Values
  4. Kéo Seasonality vào Legend

#### Biểu Đồ 3: Tác Động Khuyến Mãi
- **Loại**: Heatmap
- **Rows**: Weather_Condition
- **Columns**: Holiday_Promotion
- **Values**: Avg_Sales
- **Cách tạo**:
  1. Import query 3 vào Power BI
  2. Sử dụng Matrix visualization
  3. Cấu hình Conditional Formatting

#### Biểu Đồ 4: Phân Tích Giá Cả
- **Loại**: Scatter Chart
- **Trục X**: Avg_Our_Price
- **Trục Y**: Avg_Sales
- **Size**: Price_Difference
- **Legend**: Pricing_Strategy

#### Biểu Đồ 5: Tình Trạng Tồn Kho
- **Loại**: Bubble Chart
- **Trục X**: Forecast_Error
- **Trục Y**: Inventory_Excess
- **Size**: Avg_Inventory
- **Legend**: Inventory_Status

### 3.3. Dashboard Layout

Tạo dashboard với layout:
- **Row 1**: Biểu đồ xu hướng thời gian (Line Chart)
- **Row 2**: Doanh số theo khu vực (Column Chart) và Tác động khuyến mãi (Heatmap)
- **Row 3**: Phân tích giá cả (Scatter Chart) và Tình trạng tồn kho (Bubble Chart)

---

## Bước 4: Kết Nối Spark với Doris (WSL Ubuntu 22.04)

### 4.1. Cấu Hình Spark để Kết Nối Doris

```bash
# Trong WSL Ubuntu 22.04, cấu hình Spark
export SPARK_HOME=/opt/spark
export PATH=$PATH:$SPARK_HOME/bin:$SPARK_HOME/sbin

# Tạo file cấu hình Spark
cat > $SPARK_HOME/conf/spark-defaults.conf << EOF
spark.sql.adaptive.enabled=true
spark.sql.adaptive.coalescePartitions.enabled=true
spark.serializer=org.apache.spark.serializer.KryoSerializer
spark.sql.execution.arrow.pyspark.enabled=true
EOF
```

### 4.2. Cài Đặt MySQL Connector cho Spark

```bash
# Tải MySQL Connector
wget https://repo1.maven.org/maven2/mysql/mysql-connector-java/8.0.33/mysql-connector-java-8.0.33.jar

# Copy vào thư mục jars của Spark
sudo cp mysql-connector-java-8.0.33.jar $SPARK_HOME/jars/
```

### 4.3. Script Python để Kết Nối Spark-Doris

```python
# spark_doris_connection.py
from pyspark.sql import SparkSession
from pyspark.sql.functions import *

# Khởi tạo Spark Session
spark = SparkSession.builder \
    .appName("DorisConnection") \
    .config("spark.jars", "/opt/spark/jars/mysql-connector-java-8.0.33.jar") \
    .getOrCreate()

# Kết nối đến Doris và đọc dữ liệu
doris_df = spark.read \
    .format("jdbc") \
    .option("url", "jdbc:mysql://localhost:9030/retail_db") \
    .option("dbtable", "sales") \
    .option("user", "root") \
    .option("password", "password") \
    .load()

# Hiển thị dữ liệu
print("Dữ liệu từ Doris:")
doris_df.show(5)
doris_df.printSchema()

# Thực hiện một số phép tính
summary_df = doris_df.groupBy("region", "category") \
    .agg(
        sum("units_sold").alias("total_sales"),
        avg("price").alias("avg_price"),
        count("*").alias("record_count")
    )

summary_df.show()

# Lưu kết quả vào Doris
summary_df.write \
    .format("jdbc") \
    .option("url", "jdbc:mysql://localhost:9030/retail_db") \
    .option("dbtable", "sales_summary") \
    .option("user", "root") \
    .option("password", "password") \
    .mode("overwrite") \
    .save()

spark.stop()
```

### 4.4. Chạy Script Spark

```bash
# Chạy script Python
spark-submit \
  --master local[4] \
  --driver-memory 2g \
  --executor-memory 2g \
  spark_doris_connection.py
```

---

## Bước 5: Tích Hợp Kết Quả Data Mining vào Dashboard

### 5.1. Script Python để Xuất Kết Quả Data Mining

```python
# export_ml_results.py
import pandas as pd
import mysql.connector
from mysql.connector import Error

# Đọc kết quả từ notebook data mining
# Giả sử bạn đã có các biến: df_with_clusters, predictions_df

def export_to_doris():
    try:
        # Kết nối đến Doris
        connection = mysql.connector.connect(
            host='localhost',
            port=9030,
            database='retail_db',
            user='root',
            password='password'
        )
        
        cursor = connection.cursor()
        
        # 1. Xuất kết quả K-Means Clustering
        print("Đang xuất kết quả K-Means Clustering...")
        
        # Tạo DataFrame từ kết quả clustering
        cluster_data = []
        for idx, row in df_with_clusters.iterrows():
            cluster_data.append({
                'product_id': row['Product ID'],
                'cluster_id': row['Cluster'],
                'demand_score': row['Demand'],
                'price_score': row['Price'],
                'discount_score': row['Discount'],
                'competitor_price_score': row['Competitor Price'],
                'cluster_strategy': get_cluster_strategy(row['Cluster'])
            })
        
        cluster_df = pd.DataFrame(cluster_data)
        
        # Insert vào bảng product_clusters
        for _, row in cluster_df.iterrows():
            insert_query = """
            INSERT INTO product_clusters 
            (product_id, cluster_id, demand_score, price_score, discount_score, 
             competitor_price_score, cluster_strategy)
            VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            cursor.execute(insert_query, tuple(row))
        
        # 2. Xuất kết quả Naive Bayes Classification
        print("Đang xuất kết quả Naive Bayes Classification...")
        
        # Tạo DataFrame từ kết quả predictions
        prediction_data = []
        for idx, row in predictions_df.iterrows():
            prediction_data.append({
                'product_id': row['Product ID'],
                'store_id': row['Store ID'],
                'date': row['Date'],
                'predicted_high_sales': row['Predicted_High_Sales'],
                'prediction_probability': row['Prediction_Probability'],
                'actual_sales': row['Actual_Sales'],
                'prediction_accuracy': row['Prediction_Accuracy']
            })
        
        prediction_df = pd.DataFrame(prediction_data)
        
        # Insert vào bảng sales_predictions
        for _, row in prediction_df.iterrows():
            insert_query = """
            INSERT INTO sales_predictions 
            (product_id, store_id, date, predicted_high_sales, prediction_probability,
             actual_sales, prediction_accuracy)
            VALUES (%s, %s, %s, %s, %s, %s, %s)
            """
            cursor.execute(insert_query, tuple(row))
        
        connection.commit()
        print("Xuất dữ liệu thành công!")
        
    except Error as e:
        print(f"Lỗi kết nối: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

def get_cluster_strategy(cluster_id):
    """Xác định chiến lược dựa trên cluster ID"""
    strategies = {
        0: 'Budget Competitive',
        1: 'Premium High Demand', 
        2: 'Balanced Strategy',
        3: 'Premium Low Competition',
        4: 'Competitive Advantage'
    }
    return strategies.get(cluster_id, 'Unknown Strategy')

# Chạy hàm export
if __name__ == "__main__":
    export_to_doris()
```

### 5.2. Tạo Views Tích Hợp cho Power BI

```sql
-- View tổng hợp dữ liệu sales với kết quả clustering
CREATE VIEW sales_with_clusters AS
SELECT 
    s.*,
    pc.cluster_id,
    pc.cluster_strategy,
    pc.demand_score,
    pc.price_score,
    pc.discount_score,
    pc.competitor_price_score
FROM sales s
LEFT JOIN product_clusters pc ON s.product_id = pc.product_id;

-- View tổng hợp dữ liệu sales với predictions
CREATE VIEW sales_with_predictions AS
SELECT 
    s.*,
    sp.predicted_high_sales,
    sp.prediction_probability,
    sp.prediction_accuracy,
    CASE 
        WHEN sp.predicted_high_sales = 1 AND sp.prediction_probability > 0.8 THEN 'High Priority'
        WHEN sp.predicted_high_sales = 1 AND sp.prediction_probability > 0.6 THEN 'Medium Priority'
        WHEN sp.predicted_high_sales = 0 THEN 'Low Priority'
        ELSE 'Unknown'
    END as priority_level
FROM sales s
LEFT JOIN sales_predictions sp ON s.product_id = sp.product_id AND s.store_id = sp.store_id;

-- View dashboard tổng hợp
CREATE VIEW ml_dashboard AS
SELECT 
    s.region,
    s.category,
    s.store_id,
    s.product_id,
    s.units_sold,
    s.price,
    s.inventory_level,
    pc.cluster_strategy,
    sp.predicted_high_sales,
    sp.prediction_probability,
    sp.priority_level,
    CASE 
        WHEN pc.cluster_strategy = 'Premium High Demand' THEN 'Tăng tồn kho 30%'
        WHEN pc.cluster_strategy = 'Budget Competitive' THEN 'Tăng tồn kho 20%'
        WHEN sp.predicted_high_sales = 1 THEN 'Tăng tồn kho 25%'
        ELSE 'Giữ nguyên tồn kho'
    END as recommended_action
FROM sales s
LEFT JOIN product_clusters pc ON s.product_id = pc.product_id
LEFT JOIN sales_with_predictions sp ON s.product_id = sp.product_id AND s.store_id = sp.store_id;
```

### 5.3. Cập Nhật Dashboard Power BI

1. **Thêm Data Source mới**:
   - Kết nối đến view `ml_dashboard`
   - Import dữ liệu mới vào Power BI

2. **Tạo Biểu Đồ mới**:
   - **Cluster Strategy Distribution**: Pie chart hiển thị phân bố các chiến lược
   - **Prediction Accuracy**: Gauge chart hiển thị độ chính xác dự báo
   - **Recommended Actions**: Table hiển thị các khuyến nghị cụ thể
   - **Priority Level Analysis**: Bar chart phân tích theo mức độ ưu tiên

3. **Cập Nhật Dashboard Layout**:
   ```
   Row 1: Original Analytics (Line Chart, Column Chart)
   Row 2: ML Results (Cluster Strategy, Prediction Accuracy)
   Row 3: Recommendations (Action Table, Priority Analysis)
   ```

### 5.4. Script Tự Động Hóa Quy Trình

```bash
#!/bin/bash
# automated_pipeline.sh

echo "Bắt đầu quy trình tự động hóa..."

# 1. Chạy Spark job để xử lý dữ liệu
echo "Chạy Spark job..."
spark-submit spark_doris_connection.py

# 2. Xuất kết quả ML vào Doris
echo "Xuất kết quả ML..."
python export_ml_results.py

# 3. Cập nhật views
echo "Cập nhật views..."
mysql -h localhost -P 9030 -u root -p retail_db < update_views.sql

# 4. Refresh Power BI dataset (nếu có API)
echo "Refresh Power BI dataset..."
# curl -X POST "https://api.powerbi.com/v1.0/myorg/datasets/{dataset_id}/refreshes" \
#      -H "Authorization: Bearer {access_token}"

echo "Quy trình hoàn thành!"
```

---

## Tóm Tắt Quy Trình

1. **Bước 1**: Thiết lập database và bảng trong Apache Doris
2. **Bước 2**: Tạo 5 câu SQL phân tích dữ liệu cơ bản
3. **Bước 3**: Tạo biểu đồ trên Power BI từ SQL queries
4. **Bước 4**: Kết nối Spark với Doris trong WSL Ubuntu 22.04
5. **Bước 5**: Tích hợp kết quả data mining vào dashboard Power BI

Quy trình này tạo ra một hệ thống hoàn chỉnh từ dữ liệu thô đến insights có thể hành động, tích hợp cả phân tích truyền thống và machine learning.

---

## Kết Luận

Hướng dẫn này cung cấp một quy trình hoàn chỉnh để tích hợp Apache Doris với Power BI cho dự án data mining của bạn. Quy trình được thiết kế theo 5 bước rõ ràng:

1. **Thiết lập cơ sở dữ liệu**: Tạo database và bảng phù hợp trong Apache Doris
2. **Phân tích dữ liệu**: 5 câu SQL queries để tạo biểu đồ cơ bản trên Power BI
3. **Trực quan hóa**: Hướng dẫn chi tiết tạo dashboard trên Power BI
4. **Tích hợp Spark**: Kết nối Spark với Doris trong môi trường WSL Ubuntu 22.04
5. **Ứng dụng ML**: Tích hợp kết quả K-Means và Naive Bayes vào dashboard

### Lợi Ích Của Quy Trình Này:

- **Tính thực tiễn cao**: Từng bước đều có thể thực hiện được
- **Tích hợp hoàn chỉnh**: Kết hợp cả phân tích truyền thống và machine learning
- **Scalable**: Dễ dàng mở rộng khi dữ liệu tăng trưởng
- **Actionable Insights**: Đưa ra khuyến nghị cụ thể cho việc phân bổ hàng hóa

### Các Tính Năng Nổi Bật:

- **Real-time Analytics**: Phân tích dữ liệu theo thời gian thực
- **Predictive Insights**: Dự báo xu hướng và hành vi khách hàng
- **Automated Decision Making**: Tự động hóa các quyết định phân bổ hàng hóa
- **Comprehensive Dashboard**: Dashboard tích hợp cả dữ liệu gốc và kết quả ML

Quy trình này sẽ giúp bạn tạo ra một hệ thống Business Intelligence mạnh mẽ, phục vụ đúng mục tiêu "dự báo phân bổ hàng hóa bán lẻ" của dự án data mining.
