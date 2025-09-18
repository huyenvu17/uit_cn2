# 📊 CÁC QUERY THỐNG KÊ CHO HỆ THỐNG QUẢN LÝ HÀNG TỒN KHO BÁN LẺ

## Tổng quan về tập dữ liệu
- **Tên bảng**: `sales` trong database `retail_db`
- **Số lượng bản ghi**: 73,100 records
- **Thời gian**: Dữ liệu từ năm 2022
- **Cấu trúc**: 15 trường dữ liệu bao gồm thông tin về sản phẩm, cửa hàng, doanh số, tồn kho, giá cả, và các yếu tố ngữ cảnh

---

## 1. 📈 THỐNG KÊ TỔNG QUAN VỀ TÌNH HÌNH KINH DOANH

### 1.1. Thống kê tổng doanh thu, số lượng hàng bán ra, số cửa hàng, mức tồn kho

```sql
-- Thống kê tổng quan về tình hình kinh doanh
SELECT 
    COUNT(DISTINCT store_id) AS total_stores,
    COUNT(DISTINCT product_id) AS total_products,
    COUNT(DISTINCT category) AS total_categories,
    COUNT(DISTINCT region) AS total_regions,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    SUM(inventory_level) AS total_inventory_value,
    ROUND(AVG(inventory_level), 2) AS avg_inventory_per_product,
    COUNT(*) AS total_transactions
FROM sales 
WHERE date IS NOT NULL;
```

### 1.1.1. Tổng quan tình hình phân bổ hàng hóa toàn hệ thống

```sql
-- Tổng quan tình hình phân bổ hàng hóa toàn hệ thống
SELECT 
    'TOÀN HỆ THỐNG' AS metric,
    COUNT(DISTINCT store_id) AS total_stores,
    COUNT(DISTINCT product_id) AS total_products,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng tổng thể
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS overall_sales_rate_percent,
    -- Tính tỷ lệ đặt hàng so với bán hàng
    ROUND((SUM(units_ordered) / SUM(units_sold)) * 100, 2) AS overall_order_to_sales_ratio,
    -- Tính vòng quay hàng tồn kho tổng thể
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS overall_inventory_turnover,
    -- Tính tỷ lệ tồn kho so với bán hàng
    ROUND((SUM(inventory_level) / SUM(units_sold)) * 100, 2) AS overall_inventory_to_sales_ratio,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price
FROM sales 
WHERE date IS NOT NULL;
```

### 1.2. Thống kê theo danh mục sản phẩm

```sql
-- Thống kê doanh thu và số lượng bán theo danh mục
SELECT 
    category,
    COUNT(DISTINCT product_id) AS num_products,
    COUNT(DISTINCT store_id) AS num_stores,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_sale,
    ROUND(AVG(price), 2) AS avg_price,
    SUM(inventory_level) AS total_inventory
FROM sales 
WHERE date IS NOT NULL
GROUP BY category
ORDER BY total_revenue DESC;
```

### 1.3. Phân tích tình hình phân bổ hàng hóa hiện tại

```sql
-- Phân tích tình hình phân bổ hàng hóa theo danh mục
SELECT 
    category,
    COUNT(DISTINCT product_id) AS num_products,
    COUNT(DISTINCT store_id) AS num_stores,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng so với tổng hàng có sẵn (sold + inventory)
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS sales_rate_percent,
    -- Tính tỷ lệ đặt hàng so với hàng đã bán
    ROUND((SUM(units_ordered) / SUM(units_sold)) * 100, 2) AS order_to_sales_ratio,
    -- Tính tỷ lệ tồn kho so với hàng đã bán
    ROUND((SUM(inventory_level) / SUM(units_sold)) * 100, 2) AS inventory_to_sales_ratio,
    -- Tính vòng quay hàng tồn kho (sales/inventory)
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS inventory_turnover,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price
FROM sales 
WHERE date IS NOT NULL
GROUP BY category
ORDER BY sales_rate_percent DESC;
```

### 1.4. Phân tích tình hình phân bổ hàng hóa theo cửa hàng

```sql
-- Phân tích tình hình phân bổ hàng hóa theo cửa hàng
SELECT 
    store_id,
    region,
    COUNT(DISTINCT product_id) AS num_products,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS sales_rate_percent,
    -- Tính tỷ lệ đặt hàng so với hàng đã bán
    ROUND((SUM(units_ordered) / SUM(units_sold)) * 100, 2) AS order_to_sales_ratio,
    -- Tính vòng quay hàng tồn kho
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS inventory_turnover,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price
FROM sales 
WHERE date IS NOT NULL
GROUP BY store_id, region
ORDER BY sales_rate_percent DESC
LIMIT 20;
```

### 1.5. Phân tích tình hình phân bổ hàng hóa theo sản phẩm

```sql
-- Top 20 sản phẩm có tình hình phân bổ tốt nhất
SELECT 
    product_id,
    category,
    COUNT(DISTINCT store_id) AS stores_selling,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS sales_rate_percent,
    -- Tính vòng quay hàng tồn kho
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS inventory_turnover,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price
FROM sales 
WHERE date IS NOT NULL
GROUP BY product_id, category
HAVING total_units_sold > 0 AND total_inventory > 0
ORDER BY sales_rate_percent DESC
LIMIT 20;
```

### 1.6. Phân tích tình hình phân bổ hàng hóa theo khu vực

```sql
-- Phân tích tình hình phân bổ hàng hóa theo khu vực
SELECT 
    region,
    COUNT(DISTINCT store_id) AS num_stores,
    COUNT(DISTINCT product_id) AS num_products,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS sales_rate_percent,
    -- Tính tỷ lệ đặt hàng so với hàng đã bán
    ROUND((SUM(units_ordered) / SUM(units_sold)) * 100, 2) AS order_to_sales_ratio,
    -- Tính vòng quay hàng tồn kho
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS inventory_turnover,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price
FROM sales 
WHERE date IS NOT NULL
GROUP BY region
ORDER BY sales_rate_percent DESC;
```

### 1.7. Phân tích tình hình phân bổ hàng hóa theo thời gian

```sql
-- Phân tích tình hình phân bổ hàng hóa theo tháng
SELECT 
    YEAR(date) AS year,
    MONTH(date) AS month,
    COUNT(DISTINCT store_id) AS active_stores,
    COUNT(DISTINCT product_id) AS active_products,
    SUM(units_sold) AS total_units_sold,
    SUM(units_ordered) AS total_units_ordered,
    SUM(inventory_level) AS total_inventory,
    -- Tính tỷ lệ bán hàng theo tháng
    ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS monthly_sales_rate_percent,
    -- Tính tỷ lệ đặt hàng so với bán hàng
    ROUND((SUM(units_ordered) / SUM(units_sold)) * 100, 2) AS monthly_order_to_sales_ratio,
    -- Tính vòng quay hàng tồn kho theo tháng
    ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS monthly_inventory_turnover,
    ROUND(SUM(units_sold * price), 2) AS monthly_revenue
FROM sales 
WHERE date IS NOT NULL
GROUP BY YEAR(date), MONTH(date)
ORDER BY year, month;
```

### 1.8. So sánh hiệu suất phân bổ giữa các cửa hàng

```sql
-- So sánh hiệu suất phân bổ hàng hóa giữa các cửa hàng (Top 10 tốt nhất và 10 kém nhất)
WITH store_performance AS (
    SELECT 
        store_id,
        region,
        COUNT(DISTINCT product_id) AS num_products,
        SUM(units_sold) AS total_units_sold,
        SUM(units_ordered) AS total_units_ordered,
        SUM(inventory_level) AS total_inventory,
        -- Tính tỷ lệ bán hàng
        ROUND((SUM(units_sold) / (SUM(units_sold) + SUM(inventory_level))) * 100, 2) AS sales_rate_percent,
        -- Tính vòng quay hàng tồn kho
        ROUND(SUM(units_sold) / SUM(inventory_level), 2) AS inventory_turnover,
        ROUND(SUM(units_sold * price), 2) AS total_revenue
    FROM sales 
    WHERE date IS NOT NULL
    GROUP BY store_id, region
),
performance_ranking AS (
    SELECT 
        *,
        ROW_NUMBER() OVER (ORDER BY sales_rate_percent DESC) AS best_rank,
        ROW_NUMBER() OVER (ORDER BY sales_rate_percent ASC) AS worst_rank
    FROM store_performance
)
SELECT 
    CASE 
        WHEN best_rank <= 10 THEN 'TOP 10 TỐT NHẤT'
        WHEN worst_rank <= 10 THEN 'TOP 10 KÉM NHẤT'
    END AS performance_category,
    store_id,
    region,
    num_products,
    total_units_sold,
    total_units_ordered,
    total_inventory,
    sales_rate_percent,
    inventory_turnover,
    total_revenue
FROM performance_ranking 
WHERE best_rank <= 10 OR worst_rank <= 10
ORDER BY performance_category, sales_rate_percent DESC;
```

### 📊 GIẢI THÍCH CÁC CHỈ SỐ PHÂN TÍCH TÌNH HÌNH PHÂN BỔ HÀNG HÓA

#### 1. **Sales Rate Percent (Tỷ lệ bán hàng)**
- **Công thức**: `(units_sold / (units_sold + inventory_level)) * 100`
- **Ý nghĩa**: Phần trăm hàng hóa đã được bán ra so với tổng hàng hóa có sẵn
- **Giá trị tốt**: 70-90% (cho thấy hàng hóa bán chạy, không bị tồn kho)
- **Cảnh báo**: 
  - > 95%: Có thể thiếu hàng, cần tăng đặt hàng
  - < 50%: Hàng tồn kho nhiều, cần giảm giá hoặc tăng cường marketing

#### 2. **Order to Sales Ratio (Tỷ lệ đặt hàng so với bán hàng)**
- **Công thức**: `(units_ordered / units_sold) * 100`
- **Ý nghĩa**: Tỷ lệ hàng đặt mới so với hàng đã bán
- **Giá trị tốt**: 80-120% (đảm bảo có đủ hàng cho tương lai)
- **Cảnh báo**:
  - > 150%: Đặt hàng quá nhiều, có thể dư thừa
  - < 60%: Đặt hàng ít, có thể thiếu hàng

#### 3. **Inventory to Sales Ratio (Tỷ lệ tồn kho so với bán hàng)**
- **Công thức**: `(inventory_level / units_sold) * 100`
- **Ý nghĩa**: Tỷ lệ hàng tồn kho hiện tại so với hàng đã bán
- **Giá trị tốt**: 20-50% (đủ hàng cho 1-2 tháng bán)
- **Cảnh báo**:
  - > 100%: Tồn kho quá nhiều, cần giảm giá
  - < 10%: Tồn kho thấp, có thể thiếu hàng

#### 4. **Inventory Turnover (Vòng quay hàng tồn kho)**
- **Công thức**: `units_sold / inventory_level`
- **Ý nghĩa**: Số lần hàng tồn kho được quay vòng trong kỳ
- **Giá trị tốt**: 2-6 lần/năm (tùy loại sản phẩm)
- **Cảnh báo**:
  - > 10: Hàng bán quá nhanh, có thể thiếu hàng
  - < 1: Hàng tồn kho lâu, cần xử lý

#### 🎯 **CÁCH SỬ DỤNG CÁC CHỈ SỐ NÀY:**

1. **Phân tích theo danh mục**: Xem danh mục nào có tình hình phân bổ tốt nhất
2. **Phân tích theo cửa hàng**: Xác định cửa hàng nào quản lý tồn kho hiệu quả
3. **Phân tích theo sản phẩm**: Tìm sản phẩm có hiệu suất bán hàng cao
4. **Phân tích theo khu vực**: So sánh hiệu quả phân bổ giữa các khu vực

#### 📈 **HÀNH ĐỘNG DỰA TRÊN KẾT QUẢ:**

**Với Sales Rate cao (>80%):**
- Tăng cường đặt hàng để tránh thiếu hàng
- Mở rộng phân phối đến nhiều cửa hàng hơn

**Với Sales Rate thấp (<50%):**
- Xem xét giảm giá hoặc khuyến mãi
- Tăng cường marketing cho sản phẩm
- Giảm đặt hàng trong tương lai

**Với Inventory Turnover thấp (<1):**
- Kiểm tra chất lượng sản phẩm
- Xem xét chiến lược định giá
- Tìm cách tăng doanh số bán hàng

---

## 2. 📅 THỐNG KÊ DOANH THU THEO THỜI GIAN

### 2.1. Doanh thu theo tháng

```sql
-- Doanh thu theo tháng năm 2022
SELECT 
    YEAR(date) AS year,
    MONTH(date) AS month,
    COUNT(DISTINCT store_id) AS active_stores,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS monthly_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_daily_revenue,
    COUNT(DISTINCT date) AS active_days
FROM sales 
WHERE date IS NOT NULL
GROUP BY YEAR(date), MONTH(date)
ORDER BY year, month;
```

### 2.2. Doanh thu theo mùa

```sql
-- Doanh thu theo mùa
SELECT 
    seasonality,
    COUNT(DISTINCT store_id) AS active_stores,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS seasonal_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    ROUND(AVG(discount), 2) AS avg_discount_percent
FROM sales 
WHERE date IS NOT NULL
GROUP BY seasonality
ORDER BY seasonal_revenue DESC;
```

### 2.3. Doanh thu theo ngày trong tuần

```sql
-- Doanh thu theo ngày trong tuần
SELECT 
    CASE DAYOFWEEK(date)
        WHEN 1 THEN 'Chủ Nhật'
        WHEN 2 THEN 'Thứ Hai'
        WHEN 3 THEN 'Thứ Ba'
        WHEN 4 THEN 'Thứ Tư'
        WHEN 5 THEN 'Thứ Năm'
        WHEN 6 THEN 'Thứ Sáu'
        WHEN 7 THEN 'Thứ Bảy'
    END AS day_of_week,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS daily_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction
FROM sales 
WHERE date IS NOT NULL
GROUP BY DAYOFWEEK(date)
ORDER BY daily_revenue DESC;
```

---

## 3. 🏆 TOP SẢN PHẨM BÁN CHẠY

### 3.1. Top 10 sản phẩm bán chạy nhất

```sql
-- Top 10 sản phẩm bán chạy nhất
SELECT 
    product_id,
    category,
    COUNT(DISTINCT store_id) AS stores_selling,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price,
    ROUND(AVG(discount), 2) AS avg_discount_percent,
    SUM(inventory_level) AS total_inventory
FROM sales 
WHERE date IS NOT NULL
GROUP BY product_id, category
ORDER BY total_units_sold DESC
LIMIT 10;
```

### 3.2. Top sản phẩm theo doanh thu

```sql
-- Top 10 sản phẩm có doanh thu cao nhất
SELECT 
    product_id,
    category,
    COUNT(DISTINCT store_id) AS stores_selling,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(price), 2) AS avg_price,
    ROUND((SUM(units_sold * price) / SUM(units_sold)), 2) AS revenue_per_unit
FROM sales 
WHERE date IS NOT NULL
GROUP BY product_id, category
ORDER BY total_revenue DESC
LIMIT 10;
```

---

## 4. 🌍 THỐNG KÊ DOANH THU THEO KHU VỰC

### 4.1. Doanh thu theo khu vực

```sql
-- Doanh thu theo khu vực
SELECT 
    region,
    COUNT(DISTINCT store_id) AS num_stores,
    COUNT(DISTINCT product_id) AS num_products,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS regional_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    ROUND(AVG(inventory_level), 2) AS avg_inventory_per_product,
    ROUND(AVG(discount), 2) AS avg_discount_percent
FROM sales 
WHERE date IS NOT NULL
GROUP BY region
ORDER BY regional_revenue DESC;
```

### 4.2. Top sản phẩm theo khu vực

```sql
-- Top 5 sản phẩm bán chạy nhất theo từng khu vực
WITH regional_products AS (
    SELECT 
        region,
        product_id,
        category,
        SUM(units_sold) AS total_units_sold,
        ROUND(SUM(units_sold * price), 2) AS total_revenue,
        ROW_NUMBER() OVER (PARTITION BY region ORDER BY SUM(units_sold) DESC) AS rn
    FROM sales 
    WHERE date IS NOT NULL
    GROUP BY region, product_id, category
)
SELECT 
    region,
    product_id,
    category,
    total_units_sold,
    total_revenue
FROM regional_products 
WHERE rn <= 5
ORDER BY region, rn;
```

---

## 5. 📦 PHÂN BỐ HÀNG HÓA THEO KHU VỰC

### 5.1. Phân bố tồn kho theo khu vực

```sql
-- Phân bố tồn kho theo khu vực
SELECT 
    region,
    COUNT(DISTINCT product_id) AS num_products,
    SUM(inventory_level) AS total_inventory_value,
    ROUND(AVG(inventory_level), 2) AS avg_inventory_per_product,
    ROUND(MIN(inventory_level), 2) AS min_inventory,
    ROUND(MAX(inventory_level), 2) AS max_inventory,
    ROUND(STDDEV(inventory_level), 2) AS std_inventory
FROM sales 
WHERE date IS NOT NULL
GROUP BY region
ORDER BY total_inventory_value DESC;
```

### 5.2. Phân bố danh mục sản phẩm theo khu vực

```sql
-- Phân bố danh mục sản phẩm theo khu vực
SELECT 
    region,
    category,
    COUNT(DISTINCT product_id) AS num_products,
    COUNT(DISTINCT store_id) AS num_stores,
    SUM(inventory_level) AS total_inventory,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS category_revenue_in_region
FROM sales 
WHERE date IS NOT NULL
GROUP BY region, category
ORDER BY region, category_revenue_in_region DESC;
```

---

## 6. 🎯 PHÂN TÍCH HÀNG BÁN CHẠY

### 6.1. Phân loại hàng bán chạy theo danh mục

```sql
-- Phân loại hàng bán chạy theo danh mục
SELECT 
    category,
    COUNT(DISTINCT product_id) AS total_products,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold), 2) AS avg_units_sold_per_product,
    ROUND(AVG(price), 2) AS avg_price,
    ROUND(AVG(discount), 2) AS avg_discount_percent,
    -- Tính tỷ lệ sản phẩm có doanh số cao (trên trung bình)
    ROUND((COUNT(CASE WHEN units_sold > (SELECT AVG(units_sold) FROM sales WHERE date IS NOT NULL) THEN 1 END) * 100.0 / COUNT(*)), 2) AS high_sales_percentage
FROM sales 
WHERE date IS NOT NULL
GROUP BY category
ORDER BY total_revenue DESC;
```

### 6.2. Phân tích tác động của khuyến mãi

```sql
-- Phân tích tác động của khuyến mãi và ngày lễ
SELECT 
    CASE 
        WHEN holiday_promotion = 1 THEN 'Có Khuyến mãi/Lễ'
        ELSE 'Không có Khuyến mãi/Lễ'
    END AS promotion_status,
    COUNT(*) AS total_transactions,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold), 2) AS avg_units_sold,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    ROUND(AVG(discount), 2) AS avg_discount_percent
FROM sales 
WHERE date IS NOT NULL
GROUP BY holiday_promotion
ORDER BY total_revenue DESC;
```

---

## 7. 🌤️ PHÂN TÍCH THEO ĐIỀU KIỆN THỜI TIẾT

```sql
-- Phân tích doanh thu theo điều kiện thời tiết
SELECT 
    weather_condition,
    COUNT(*) AS total_transactions,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold), 2) AS avg_units_sold,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    ROUND(AVG(discount), 2) AS avg_discount_percent
FROM sales 
WHERE date IS NOT NULL
GROUP BY weather_condition
ORDER BY total_revenue DESC;
```

---

## 8. 📊 THỐNG KÊ HIỆU SUẤT CỬA HÀNG

### 8.1. Top cửa hàng có doanh thu cao nhất

```sql
-- Top 10 cửa hàng có doanh thu cao nhất
SELECT 
    store_id,
    region,
    COUNT(DISTINCT product_id) AS num_products,
    SUM(units_sold) AS total_units_sold,
    ROUND(SUM(units_sold * price), 2) AS total_revenue,
    ROUND(AVG(units_sold * price), 2) AS avg_revenue_per_transaction,
    ROUND(AVG(inventory_level), 2) AS avg_inventory_level
FROM sales 
WHERE date IS NOT NULL
GROUP BY store_id, region
ORDER BY total_revenue DESC
LIMIT 10;
```

### 8.2. Hiệu suất cửa hàng theo khu vực

```sql
-- Hiệu suất cửa hàng theo khu vực
SELECT 
    region,
    COUNT(DISTINCT store_id) AS num_stores,
    ROUND(SUM(units_sold * price) / COUNT(DISTINCT store_id), 2) AS avg_revenue_per_store,
    ROUND(AVG(inventory_level), 2) AS avg_inventory_per_store,
    ROUND(SUM(units_sold) / COUNT(DISTINCT store_id), 2) AS avg_units_sold_per_store
FROM sales 
WHERE date IS NOT NULL
GROUP BY region
ORDER BY avg_revenue_per_store DESC;
```

---

## 9. 🔍 CÁC QUERY PHÂN TÍCH CHUYÊN SÂU

### 9.1. Phân tích xu hướng giá cả

```sql
-- Phân tích xu hướng giá cả theo thời gian
SELECT 
    MONTH(date) AS month,
    category,
    ROUND(AVG(price), 2) AS avg_price,
    ROUND(AVG(competitor_pricing), 2) AS avg_competitor_price,
    ROUND((AVG(price) - AVG(competitor_pricing)), 2) AS price_difference,
    ROUND(AVG(discount), 2) AS avg_discount
FROM sales 
WHERE date IS NOT NULL
GROUP BY MONTH(date), category
ORDER BY month, category;
```

### 9.2. Phân tích dự báo nhu cầu

```sql
-- So sánh dự báo nhu cầu với thực tế
SELECT 
    category,
    ROUND(AVG(demand_forecast), 2) AS avg_forecasted_demand,
    ROUND(AVG(units_sold), 2) AS avg_actual_sales,
    ROUND((AVG(units_sold) - AVG(demand_forecast)), 2) AS forecast_accuracy,
    ROUND(((AVG(units_sold) - AVG(demand_forecast)) / AVG(demand_forecast) * 100), 2) AS forecast_error_percentage
FROM sales 
WHERE date IS NOT NULL
GROUP BY category
ORDER BY forecast_error_percentage;
```

---

## 📝 GHI CHÚ QUAN TRỌNG

1. **Lọc dữ liệu**: Tất cả các query đều sử dụng `WHERE date IS NOT NULL` để loại bỏ dòng header của CSV
2. **Định dạng số**: Sử dụng `ROUND()` để làm tròn kết quả đến 2 chữ số thập phân
3. **Hiệu suất**: Với dataset lớn (73K+ records), nên tạo index trên các cột thường được filter như `date`, `store_id`, `product_id`, `region`
4. **Mở rộng**: Có thể thêm các phân tích theo tuần, quý hoặc so sánh year-over-year khi có dữ liệu nhiều năm hơn

---

## 🚀 CÁCH SỬ DỤNG

1. **Kết nối đến Apache Doris**:
   ```bash
   mysql -h 127.0.0.1 -P 9030 -u root -p retail_db
   ```

2. **Chạy các query**:
   - Copy từng query SQL và paste vào terminal hoặc tool kết nối Doris
   - Điều chỉnh `LIMIT` nếu cần để giảm thời gian thực thi
   - Export kết quả để phân tích thêm trong Excel/PowerBI

3. **Tối ưu hóa**:
   - Tạo view cho các query thường dùng
   - Sử dụng materialized view cho các báo cáo phức tạp
   - Lưu kết quả vào bảng tạm cho việc phân tích tiếp theo
