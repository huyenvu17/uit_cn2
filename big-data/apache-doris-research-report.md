# Báo Cáo Nghiên Cứu: Apache Doris - Hệ Thống Phân Tích Dữ Liệu Thời Gian Thực

## 1. Giới Thiệu

Apache Doris là một hệ quản trị cơ sở dữ liệu phân tích thời gian thực mã nguồn mở, được thiết kế dựa trên kiến trúc MPP (Massively Parallel Processing). Được phát triển ban đầu bởi Baidu và sau đó trở thành dự án Apache top-level, Doris được tối ưu hóa để xử lý các truy vấn phân tích phức tạp trên khối lượng dữ liệu lớn với độ trễ thấp.

### Lịch Sử Phát Triển
- **2017**: Bắt đầu phát triển tại Baidu với tên gọi Palo
- **2018**: Mã nguồn mở với tên Apache Doris (incubating)
- **2022**: Trở thành dự án Apache top-level
- **2024**: Phát hành phiên bản 3.0 với nhiều tính năng mới

### Định Vị Trong Hệ Sinh Thái Big Data
Apache Doris được định vị như một Modern Data Warehouse, kết hợp khả năng xử lý OLAP (Online Analytical Processing) truyền thống với tính năng phân tích thời gian thực, phù hợp cho các ứng dụng từ báo cáo kinh doanh đến phân tích IoT.

## 2. Đặc Điểm Nổi Bật

### 2.1 Kiến Trúc MPP Hiện Đại
- **Frontend (FE)**: Quản lý metadata, lập kế hoạch truy vấn và điều phối
- **Backend (BE)**: Thực thi truy vấn và lưu trữ dữ liệu
- **Broker**: Hỗ trợ import dữ liệu từ các nguồn bên ngoài

### 2.2 Hiệu Suất Cao
- **Vectorized Execution Engine**: Tăng tốc xử lý truy vấn lên 5-10 lần
- **Columnar Storage**: Tối ưu hóa cho các truy vấn phân tích
- **Intelligent Indexing**: Bitmap index, BloomFilter, Zone Map
- **Query Cache**: Giảm thời gian phản hồi cho các truy vấn lặp lại

### 2.3 Khả Năng Mở Rộng
- **Horizontal Scaling**: Thêm node một cách linh hoạt
- **Auto Rebalancing**: Tự động cân bằng tải khi thêm/bớt node
- **Multi-tenant**: Hỗ trợ nhiều tenant trên cùng cluster

### 2.4 Tính Năng Thời Gian Thực
- **Stream Load**: Import dữ liệu real-time từ Kafka, Flink
- **Routine Load**: Tự động đồng bộ dữ liệu liên tục
- **Materialized Views**: Tính toán trước kết quả cho truy vấn nhanh

### 2.5 Tương Thích Cao
- **MySQL Protocol**: Tương thích với các công cụ BI phổ biến
- **Standard SQL**: Hỗ trợ SQL-2003 standard
- **Ecosystem Integration**: Kết nối với Spark, Flink, Kafka, HDFS

## 3. Ứng Dụng Thực Tế

### 3.1 Phân Tích Hàng Tồn Kho Thời Gian Thực

#### Thách Thức Hiện Tại
Quản lý hàng tồn kho trong thời đại thương mại điện tử đòi hỏi:
- Theo dõi mức tồn kho real-time trên nhiều kênh bán hàng
- Dự báo nhu cầu dựa trên xu hướng mua sắm
- Tối ưu hóa chuỗi cung ứng và giảm thiểu chi phí lưu kho
- Phát hiện sớm tình trạng hết hàng hoặc tồn kho thừa

#### Giải Pháp Apache Doris
**Kiến Trúc Đề Xuất:**
```
[POS Systems] → [Kafka] → [Apache Doris] → [BI Dashboard]
[E-commerce] → [Stream Load] → [Real-time Analytics] → [Alerts]
[Warehouse Management] → [Routine Load] → [Inventory Optimization]
```

**Lợi Ích Cụ Thể:**
- **Visibility Real-time**: Cập nhật tồn kho mỗi giây từ tất cả điểm bán
- **Predictive Analytics**: Sử dụng ML models để dự báo nhu cầu
- **Cost Optimization**: Giảm 15-25% chi phí lưu kho thông qua tối ưu hóa
- **Risk Mitigation**: Cảnh báo sớm tình trạng thiếu hàng

### 3.2 Theo Dõi Giao Thông TP.HCM Thời Gian Thực

#### Bối Cảnh Thành Phố Thông Minh
TP.HCM với hơn 10 triệu dân và mật độ giao thông cao cần:
- Giám sát tình trạng giao thông real-time
- Tối ưu hóa tín hiệu đèn giao thông thông minh
- Phát hiện và xử lý ùn tắc nhanh chóng
- Phân tích pattern giao thông để quy hoạch đô thị

#### Giải Pháp Apache Doris
**Kiến Trúc Hệ Thống:**
```
[Traffic Cameras] → [Edge Computing] → [MQTT/Kafka] → [Apache Doris]
[GPS Devices] → [Real-time Stream] → [Stream Processing] → [Analytics Engine]
[IoT Sensors] → [Data Pipeline] → [Time-series Storage] → [Smart Dashboard]
```

**Tính Năng Chính:**
- **Real-time Traffic Monitoring**: Xử lý 1M+ events/second từ sensors
- **Predictive Traffic Management**: Dự báo ùn tắc trước 15-30 phút
- **Dynamic Route Optimization**: Đề xuất tuyến đường tối ưu real-time
- **Emergency Response**: Phát hiện tai nạn và điều phối cứu hộ

## 4. Cách Cài Đặt và Sử Dụng

### 4.1 Tổng Quan Các Phương Pháp Cài Đặt

Apache Doris hỗ trợ nhiều phương pháp cài đặt phù hợp với các môi trường khác nhau:

| Phương Pháp | Ưu Điểm | Nhược Điểm | Phù Hợp Cho |
|-------------|---------|------------|-------------|
| **Binary Installation** | Hiệu suất cao, tùy chỉnh tối đa | Phức tạp, quản lý thủ công | Production, Large-scale |
| **Docker** | Dễ triển khai, portable | Overhead nhẹ | Development, Testing |
| **Kubernetes** | Auto-scaling, HA | Phức tạp setup | Cloud-native, Enterprise |
| **Cloud Services** | Managed, no-ops | Vendor lock-in, chi phí | Quick start, POC |

### 4.2 Yêu Cầu Hệ Thống

#### Yêu Cầu Tối Thiểu
- **CPU**: 4 cores (khuyến nghị 8+ cores)
- **Memory**: 8GB RAM (khuyến nghị 16GB+)
- **Storage**: 100GB+ (SSD khuyến nghị)
- **Network**: 1Gbps+ bandwidth
- **OS**: Linux (CentOS 7+, Ubuntu 18.04+), macOS, Windows (với WSL)

#### Yêu Cầu cho Production
- **CPU**: 16+ cores per node
- **Memory**: 64GB+ RAM per node
- **Storage**: 1TB+ NVMe SSD
- **Network**: 10Gbps+ với low latency
- **HA Setup**: Tối thiểu 3 FE nodes, 3+ BE nodes

### 4.3 Phương Pháp Cài Đặt Được Nhóm Lựa Chọn: Docker trên WSL

#### 4.3.1 Tại Sao Chọn Docker trên WSL?

**Lý do lựa chọn:**
- ✅ **Cross-platform**: Chạy trên Windows mà không cần dual-boot
- ✅ **Isolation**: Container cô lập, không ảnh hưởng hệ thống host
- ✅ **Reproducible**: Đảm bảo môi trường nhất quán giữa các thành viên
- ✅ **Easy cleanup**: Xóa container mà không để lại "rác"
- ✅ **Version management**: Dễ dàng switch giữa các phiên bản Doris
- ✅ **Development friendly**: Phù hợp cho học tập và thử nghiệm

**So sánh với các phương pháp khác:**
```
Native Linux Install:  ████████████ (Hiệu suất cao nhưng phức tạp)
Docker on WSL:         ██████████   (Cân bằng tốt giữa dễ dùng và hiệu suất)
Windows Native:        ████         (Không được hỗ trợ chính thức)
Virtual Machine:       ██████       (Overhead cao, chậm)
```

#### 4.3.2 Chuẩn Bị Môi Trường WSL

**Bước 1: Cài đặt WSL2**
```powershell
# Chạy PowerShell as Administrator
# Enable WSL feature
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

# Enable Virtual Machine Platform
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

# Restart máy tính
# Sau khi restart, set WSL2 as default
wsl --set-default-version 2

# Cài đặt Ubuntu 22.04 LTS
wsl --install -d Ubuntu-22.04
```

**Bước 2: Cấu hình WSL2**
```bash
# Trong WSL Ubuntu terminal
# Update system
sudo apt update && sudo apt upgrade -y

# Cài đặt các tools cần thiết
sudo apt install -y curl wget git vim htop

# Kiểm tra WSL version
wsl -l -v
```

**Bước 3: Cài đặt Docker trong WSL2**
```bash
# Cài đặt Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh

# Thêm user vào docker group
sudo usermod -aG docker $USER

# Khởi động Docker service
sudo service docker start

# Enable Docker auto-start
echo 'sudo service docker start' >> ~/.bashrc

# Kiểm tra Docker
docker --version
docker run hello-world
```

#### 4.3.3 Cài Đặt Apache Doris với Docker

**Bước 1: Tạo Docker Network**
```bash
# Tạo custom network cho Doris cluster
docker network create doris-network

# Kiểm tra network
docker network ls
```

**Bước 2: Tạo Thư Mục Dữ Liệu**
```bash
# Tạo thư mục cho persistent storage
mkdir -p ~/doris-docker/{fe-meta,be-storage,logs}
cd ~/doris-docker

# Set permissions
chmod -R 755 ~/doris-docker
```

**Bước 3: Tạo Docker Compose File**
```bash
# Tạo docker-compose.yml
cat > docker-compose.yml << 'EOF'
version: '3.8'

services:
  doris-fe:
    image: apache/doris:2.1.0-fe-x86_64
    container_name: doris-fe
    hostname: doris-fe
    ports:
      - "8030:8030"  # HTTP port
      - "9010:9010"  # RPC port
      - "9020:9020"  # Edit log port
      - "9030:9030"  # MySQL protocol port
    volumes:
      - ./fe-meta:/opt/apache-doris/fe/doris-meta
      - ./logs/fe:/opt/apache-doris/fe/log
    environment:
      - FE_SERVERS=fe1:doris-fe:9010
      - FE_ID=1
    networks:
      - doris-network
    restart: unless-stopped
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:8030/api/health"]
      interval: 30s
      timeout: 10s
      retries: 3

  doris-be:
    image: apache/doris:2.1.0-be-x86_64
    container_name: doris-be
    hostname: doris-be
    ports:
      - "8040:8040"  # HTTP port
      - "9050:9050"  # RPC port
      - "8060:8060"  # Brpc port
    volumes:
      - ./be-storage:/opt/apache-doris/be/storage
      - ./logs/be:/opt/apache-doris/be/log
    environment:
      - FE_SERVERS=doris-fe:9010
      - BE_ADDR=doris-be:9050
    networks:
      - doris-network
    depends_on:
      doris-fe:
        condition: service_healthy
    restart: unless-stopped

networks:
  doris-network:
    driver: bridge
    ipam:
      config:
        - subnet: 172.20.0.0/16
EOF
```

**Bước 4: Khởi Động Doris Cluster**
```bash
# Pull images (optional, sẽ tự động pull khi start)
docker-compose pull

# Start services
docker-compose up -d

# Kiểm tra status
docker-compose ps

# Xem logs
docker-compose logs -f doris-fe
docker-compose logs -f doris-be
```

**Bước 5: Thêm BE Node vào Cluster**
```bash
# Kết nối MySQL client
mysql -h 127.0.0.1 -P 9030 -u root

# Trong MySQL prompt
SHOW FRONTENDS;
ALTER SYSTEM ADD BACKEND "doris-be:9050";
SHOW BACKENDS;
```

#### 4.3.4 Cấu Hình Nâng Cao

**Tùy chỉnh FE Configuration**
```bash
# Tạo custom fe.conf
cat > fe-custom.conf << 'EOF'
# Basic settings
priority_networks = 172.20.0.0/16
meta_dir = /opt/apache-doris/fe/doris-meta
http_port = 8030
rpc_port = 9020
query_port = 9030
edit_log_port = 9010

# Performance tuning
max_connection = 4096
qe_max_connection = 1024
max_query_retry_time = 3

# Memory settings
max_heap_size_gb = 8
EOF

# Mount custom config trong docker-compose.yml
# Thêm vào volumes của doris-fe:
# - ./fe-custom.conf:/opt/apache-doris/fe/conf/fe.conf
```

**Tùy chỉnh BE Configuration**
```bash
# Tạo custom be.conf
cat > be-custom.conf << 'EOF'
# Basic settings
priority_networks = 172.20.0.0/16
storage_root_path = /opt/apache-doris/be/storage
be_port = 9060
webserver_port = 8040
heartbeat_service_port = 9050
brpc_port = 8060

# Performance tuning
be_rpc_port = 9070
max_tablet_num_per_shard = 1024
default_num_rows_per_column_file_block = 1024

# Memory settings
mem_limit = 80%
EOF
```

#### 4.3.5 Monitoring và Troubleshooting

**Health Check Scripts**
```bash
# Tạo script kiểm tra health
cat > check-doris-health.sh << 'EOF'
#!/bin/bash

echo "=== Doris Cluster Health Check ==="

# Check containers
echo "1. Container Status:"
docker-compose ps

# Check FE health
echo -e "\n2. Frontend Health:"
curl -s http://localhost:8030/api/health | jq '.'

# Check BE status
echo -e "\n3. Backend Status:"
mysql -h 127.0.0.1 -P 9030 -u root -e "SHOW BACKENDS\G"

# Check disk usage
echo -e "\n4. Storage Usage:"
du -sh ~/doris-docker/*

# Check logs for errors
echo -e "\n5. Recent Errors:"
docker-compose logs --tail=50 doris-fe | grep -i error
docker-compose logs --tail=50 doris-be | grep -i error
EOF

chmod +x check-doris-health.sh
```

**Performance Monitoring**
```bash
# Tạo monitoring script
cat > monitor-doris.sh << 'EOF'
#!/bin/bash

# Resource usage
echo "=== Resource Usage ==="
docker stats --no-stream doris-fe doris-be

# Query performance
echo -e "\n=== Query Performance ==="
mysql -h 127.0.0.1 -P 9030 -u root -e "
SHOW QUERY PROFILE;
SHOW PROCESSLIST;
"

# Storage metrics
echo -e "\n=== Storage Metrics ==="
mysql -h 127.0.0.1 -P 9030 -u root -e "
SHOW TABLETS;
SHOW DATA;
"
EOF

chmod +x monitor-doris.sh
```

**Common Issues và Solutions**
```bash
# Issue 1: Container không start
# Solution: Check logs và port conflicts
docker-compose logs doris-fe
netstat -tulpn | grep :8030

# Issue 2: BE không join cluster
# Solution: Check network connectivity
docker exec doris-fe ping doris-be
mysql -h 127.0.0.1 -P 9030 -u root -e "ALTER SYSTEM ADD BACKEND 'doris-be:9050';"

# Issue 3: Out of memory
# Solution: Adjust memory limits
# Edit docker-compose.yml thêm:
# deploy:
#   resources:
#     limits:
#       memory: 8G
```

### 4.4 Sử Dụng Cơ Bản

#### 4.4.1 Kết Nối và Quản Lý

**Kết nối qua MySQL Client**
```bash
# Cài đặt MySQL client trong WSL
sudo apt install mysql-client-core-8.0

# Kết nối Doris
mysql -h 127.0.0.1 -P 9030 -u root

# Hoặc sử dụng Docker MySQL client
docker run -it --rm --network doris-network mysql:8.0 \
  mysql -h doris-fe -P 9030 -u root
```

**Web UI Management**
```bash
# Truy cập FE Web UI
# Mở browser: http://localhost:8030
# Username: root, Password: (để trống)

# Truy cập BE Web UI
# Mở browser: http://localhost:8040
```

#### 4.4.2 Tạo Database và Table

**Tạo Database**
```sql
-- Kết nối và tạo database
mysql -h 127.0.0.1 -P 9030 -u root

-- Tạo database cho inventory management
CREATE DATABASE inventory_db;
USE inventory_db;

-- Tạo database cho traffic monitoring
CREATE DATABASE traffic_db;
```

**Tạo Table cho Inventory Management**
```sql
-- Bảng sản phẩm
CREATE TABLE products (
    product_id BIGINT,
    product_name VARCHAR(200),
    category VARCHAR(100),
    brand VARCHAR(100),
    price DECIMAL(10,2),
    created_time DATETIME
) DUPLICATE KEY(product_id)
DISTRIBUTED BY HASH(product_id) BUCKETS 10
PROPERTIES (
    "replication_num" = "1",
    "storage_format" = "V2"
);

-- Bảng tồn kho real-time
CREATE TABLE inventory_realtime (
    product_id BIGINT,
    warehouse_id INT,
    quantity INT,
    reserved_quantity INT,
    available_quantity INT,
    last_updated DATETIME,
    location VARCHAR(100),
    status VARCHAR(50)
) DUPLICATE KEY(product_id, warehouse_id, last_updated)
PARTITION BY RANGE(last_updated) (
    PARTITION p20240101 VALUES LESS THAN ("2024-02-01"),
    PARTITION p20240201 VALUES LESS THAN ("2024-03-01"),
    PARTITION p20240301 VALUES LESS THAN ("2024-04-01")
)
DISTRIBUTED BY HASH(product_id) BUCKETS 10
PROPERTIES (
    "replication_num" = "1",
    "storage_format" = "V2",
    "dynamic_partition.enable" = "true",
    "dynamic_partition.time_unit" = "MONTH",
    "dynamic_partition.start" = "-3",
    "dynamic_partition.end" = "3",
    "dynamic_partition.prefix" = "p",
    "dynamic_partition.buckets" = "10"
);

-- Bảng transactions
CREATE TABLE inventory_transactions (
    transaction_id BIGINT,
    product_id BIGINT,
    warehouse_id INT,
    transaction_type VARCHAR(50), -- IN, OUT, TRANSFER
    quantity INT,
    reference_id VARCHAR(100),
    transaction_time DATETIME,
    created_by VARCHAR(100)
) DUPLICATE KEY(transaction_id, transaction_time)
PARTITION BY RANGE(transaction_time) (
    PARTITION p20240101 VALUES LESS THAN ("2024-02-01")
)
DISTRIBUTED BY HASH(transaction_id) BUCKETS 10
PROPERTIES (
    "replication_num" = "1",
    "dynamic_partition.enable" = "true",
    "dynamic_partition.time_unit" = "DAY",
    "dynamic_partition.start" = "-7",
    "dynamic_partition.end" = "3"
);
```

**Tạo Table cho Traffic Monitoring**
```sql
USE traffic_db;

-- Bảng traffic events
CREATE TABLE traffic_events (
    event_id BIGINT,
    camera_id VARCHAR(50),
    location_lat DECIMAL(10,8),
    location_lng DECIMAL(11,8),
    vehicle_count INT,
    avg_speed DECIMAL(5,2),
    traffic_density VARCHAR(20), -- LOW, MEDIUM, HIGH, CONGESTED
    event_time DATETIME,
    weather_condition VARCHAR(50),
    road_condition VARCHAR(50)
) DUPLICATE KEY(event_id, event_time)
PARTITION BY RANGE(event_time) (
    PARTITION p20240101 VALUES LESS THAN ("2024-01-02")
)
DISTRIBUTED BY HASH(camera_id) BUCKETS 20
PROPERTIES (
    "replication_num" = "1",
    "dynamic_partition.enable" = "true",
    "dynamic_partition.time_unit" = "DAY",
    "dynamic_partition.start" = "-3",
    "dynamic_partition.end" = "1"
);

-- Bảng incidents
CREATE TABLE traffic_incidents (
    incident_id BIGINT,
    incident_type VARCHAR(50), -- ACCIDENT, BREAKDOWN, CONSTRUCTION
    location_lat DECIMAL(10,8),
    location_lng DECIMAL(11,8),
    severity VARCHAR(20), -- LOW, MEDIUM, HIGH, CRITICAL
    description TEXT,
    reported_time DATETIME,
    resolved_time DATETIME,
    status VARCHAR(20) -- ACTIVE, RESOLVED, CLOSED
) UNIQUE KEY(incident_id)
DISTRIBUTED BY HASH(incident_id) BUCKETS 10
PROPERTIES (
    "replication_num" = "1"
);
```

#### 4.4.3 Import Dữ Liệu

**Stream Load cho Real-time Data**
```bash
# Tạo sample data cho inventory
cat > sample_inventory.csv << 'EOF'
1001,1,150,10,140,"2024-01-15 10:30:00","A-01-01","ACTIVE"
1002,1,75,5,70,"2024-01-15 10:30:00","A-01-02","ACTIVE"
1003,2,200,0,200,"2024-01-15 10:30:00","B-02-01","ACTIVE"
EOF

# Stream load inventory data
curl -u root: -T sample_inventory.csv \
    -H "label:inventory_load_$(date +%s)" \
    -H "column_separator:," \
    -H "columns:product_id,warehouse_id,quantity,reserved_quantity,available_quantity,last_updated,location,status" \
    http://localhost:8030/api/inventory_db/inventory_realtime/_stream_load

# Tạo sample traffic data
cat > sample_traffic.csv << 'EOF'
1,"CAM001",10.762622,106.660172,45,35.5,"MEDIUM","2024-01-15 10:30:00","CLEAR","GOOD"
2,"CAM002",10.762822,106.660372,78,15.2,"HIGH","2024-01-15 10:30:00","CLEAR","GOOD"
EOF

# Stream load traffic data
curl -u root: -T sample_traffic.csv \
    -H "label:traffic_load_$(date +%s)" \
    -H "column_separator:," \
    -H "columns:event_id,camera_id,location_lat,location_lng,vehicle_count,avg_speed,traffic_density,event_time,weather_condition,road_condition" \
    http://localhost:8030/api/traffic_db/traffic_events/_stream_load
```

**Routine Load cho Kafka Integration**
```sql
-- Tạo routine load job cho inventory updates
CREATE ROUTINE LOAD inventory_db.inventory_routine_load ON inventory_realtime
COLUMNS(product_id,warehouse_id,quantity,reserved_quantity,available_quantity,last_updated,location,status)
PROPERTIES
(
    "desired_concurrent_number"="1",
    "max_batch_interval" = "10",
    "max_batch_rows" = "1000"
)
FROM KAFKA
(
    "kafka_broker_list" = "localhost:9092",
    "kafka_topic" = "inventory_updates",
    "property.group.id" = "doris_inventory_group"
);

-- Start routine load
RESUME ROUTINE LOAD FOR inventory_db.inventory_routine_load;
```

### 4.5 Tối Ưu Hóa Hiệu Suất

#### 4.5.1 Partitioning Strategy
```sql
-- Time-based partitioning cho time-series data
ALTER TABLE inventory_realtime ADD PARTITION p20240401 VALUES LESS THAN ("2024-05-01");

-- List partitioning cho categorical data
CREATE TABLE products_by_category (
    product_id BIGINT,
    category VARCHAR(100),
    data_col VARCHAR(200)
) DUPLICATE KEY(product_id)
PARTITION BY LIST(category) (
    PARTITION electronics VALUES IN ("Electronics", "Computers"),
    PARTITION clothing VALUES IN ("Clothing", "Fashion"),
    PARTITION books VALUES IN ("Books", "Education")
)
DISTRIBUTED BY HASH(product_id) BUCKETS 10;
```

#### 4.5.2 Indexing và Optimization
```sql
-- Tạo BloomFilter index
ALTER TABLE inventory_realtime SET ("bloom_filter_columns" = "product_id,warehouse_id");

-- Tạo Materialized View cho aggregation
CREATE MATERIALIZED VIEW inventory_summary AS
SELECT
    warehouse_id,
    DATE(last_updated) as date,
    SUM(quantity) as total_quantity,
    COUNT(DISTINCT product_id) as unique_products
FROM inventory_realtime
GROUP BY warehouse_id, DATE(last_updated);

-- Enable colocate cho join optimization
ALTER TABLE products SET ("colocate_with" = "inventory_group");
ALTER TABLE inventory_realtime SET ("colocate_with" = "inventory_group");
```

#### 4.5.3 Query Optimization Examples
```sql
-- Optimized query với partition pruning
SELECT warehouse_id, SUM(available_quantity) as total_available
FROM inventory_realtime
WHERE last_updated >= '2024-01-01' AND last_updated < '2024-02-01'
  AND warehouse_id IN (1, 2, 3)
GROUP BY warehouse_id;

-- Real-time analytics query
SELECT
    camera_id,
    AVG(vehicle_count) as avg_vehicles,
    AVG(avg_speed) as avg_speed,
    COUNT(*) as event_count
FROM traffic_events
WHERE event_time >= NOW() - INTERVAL 1 HOUR
GROUP BY camera_id
ORDER BY avg_vehicles DESC
LIMIT 10;
```

### 4.6 Backup và Recovery

#### 4.6.1 Backup Strategies
```bash
# Tạo backup script
cat > backup-doris.sh << 'EOF'
#!/bin/bash

BACKUP_DIR="/backup/doris/$(date +%Y%m%d_%H%M%S)"
mkdir -p $BACKUP_DIR

echo "Starting Doris backup..."

# 1. Backup metadata (FE)
echo "Backing up FE metadata..."
docker exec doris-fe tar -czf /tmp/fe-meta-backup.tar.gz -C /opt/apache-doris/fe doris-meta
docker cp doris-fe:/tmp/fe-meta-backup.tar.gz $BACKUP_DIR/

# 2. Backup data (BE)
echo "Backing up BE data..."
docker exec doris-be tar -czf /tmp/be-storage-backup.tar.gz -C /opt/apache-doris/be storage
docker cp doris-be:/tmp/be-storage-backup.tar.gz $BACKUP_DIR/

# 3. Backup configurations
echo "Backing up configurations..."
cp docker-compose.yml $BACKUP_DIR/
cp -r ~/doris-docker/*.conf $BACKUP_DIR/ 2>/dev/null || true

# 4. Export schema
echo "Exporting database schema..."
mysql -h 127.0.0.1 -P 9030 -u root -e "SHOW DATABASES;" > $BACKUP_DIR/databases.sql
mysql -h 127.0.0.1 -P 9030 -u root inventory_db -e "SHOW CREATE TABLE inventory_realtime\G" > $BACKUP_DIR/inventory_schema.sql

echo "Backup completed: $BACKUP_DIR"
EOF

chmod +x backup-doris.sh
```

#### 4.6.2 Automated Backup với Cron
```bash
# Thêm vào crontab
crontab -e

# Backup hàng ngày lúc 2:00 AM
0 2 * * * /home/user/doris-docker/backup-doris.sh >> /var/log/doris-backup.log 2>&1

# Cleanup old backups (giữ 7 ngày)
0 3 * * * find /backup/doris -type d -mtime +7 -exec rm -rf {} \;
```

#### 4.6.3 Recovery Process
```bash
# Recovery script
cat > restore-doris.sh << 'EOF'
#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <backup_directory>"
    exit 1
fi

BACKUP_DIR=$1

echo "Starting Doris restore from $BACKUP_DIR..."

# 1. Stop services
docker-compose down

# 2. Clear existing data
sudo rm -rf ~/doris-docker/fe-meta/*
sudo rm -rf ~/doris-docker/be-storage/*

# 3. Restore metadata
echo "Restoring FE metadata..."
tar -xzf $BACKUP_DIR/fe-meta-backup.tar.gz -C ~/doris-docker/

# 4. Restore data
echo "Restoring BE data..."
tar -xzf $BACKUP_DIR/be-storage-backup.tar.gz -C ~/doris-docker/

# 5. Restore configurations
cp $BACKUP_DIR/docker-compose.yml ./

# 6. Start services
docker-compose up -d

echo "Restore completed. Please verify cluster status."
EOF

chmod +x restore-doris.sh
```

### 4.7 Scaling và High Availability

#### 4.7.1 Horizontal Scaling
```yaml
# docker-compose-scaled.yml - Multi-node setup
version: '3.8'

services:
  doris-fe-1:
    image: apache/doris:2.1.0-fe-x86_64
    container_name: doris-fe-1
    hostname: doris-fe-1
    ports:
      - "8030:8030"
      - "9010:9010"
    environment:
      - FE_SERVERS=fe1:doris-fe-1:9010,fe2:doris-fe-2:9010,fe3:doris-fe-3:9010
      - FE_ID=1
    networks:
      - doris-network

  doris-fe-2:
    image: apache/doris:2.1.0-fe-x86_64
    container_name: doris-fe-2
    hostname: doris-fe-2
    ports:
      - "8031:8030"
      - "9011:9010"
    environment:
      - FE_SERVERS=fe1:doris-fe-1:9010,fe2:doris-fe-2:9010,fe3:doris-fe-3:9010
      - FE_ID=2
    networks:
      - doris-network

  doris-fe-3:
    image: apache/doris:2.1.0-fe-x86_64
    container_name: doris-fe-3
    hostname: doris-fe-3
    ports:
      - "8032:8030"
      - "9012:9010"
    environment:
      - FE_SERVERS=fe1:doris-fe-1:9010,fe2:doris-fe-2:9010,fe3:doris-fe-3:9010
      - FE_ID=3
    networks:
      - doris-network

  doris-be-1:
    image: apache/doris:2.1.0-be-x86_64
    container_name: doris-be-1
    hostname: doris-be-1
    ports:
      - "8040:8040"
      - "9050:9050"
    environment:
      - FE_SERVERS=doris-fe-1:9010,doris-fe-2:9010,doris-fe-3:9010
    networks:
      - doris-network

  doris-be-2:
    image: apache/doris:2.1.0-be-x86_64
    container_name: doris-be-2
    hostname: doris-be-2
    ports:
      - "8041:8040"
      - "9051:9050"
    environment:
      - FE_SERVERS=doris-fe-1:9010,doris-fe-2:9010,doris-fe-3:9010
    networks:
      - doris-network

  doris-be-3:
    image: apache/doris:2.1.0-be-x86_64
    container_name: doris-be-3
    hostname: doris-be-3
    ports:
      - "8042:8040"
      - "9052:9050"
    environment:
      - FE_SERVERS=doris-fe-1:9010,doris-fe-2:9010,doris-fe-3:9010
    networks:
      - doris-network

networks:
  doris-network:
    driver: bridge
```

#### 4.7.2 Load Balancer Setup
```bash
# Cài đặt HAProxy cho load balancing
sudo apt install haproxy

# Cấu hình HAProxy
cat > /etc/haproxy/haproxy.cfg << 'EOF'
global
    daemon
    maxconn 4096

defaults
    mode tcp
    timeout connect 5000ms
    timeout client 50000ms
    timeout server 50000ms

# MySQL protocol load balancing
listen doris-mysql
    bind *:3306
    balance roundrobin
    server fe1 127.0.0.1:9030 check
    server fe2 127.0.0.1:9031 check
    server fe3 127.0.0.1:9032 check

# HTTP API load balancing
listen doris-http
    bind *:8080
    balance roundrobin
    server fe1 127.0.0.1:8030 check
    server fe2 127.0.0.1:8031 check
    server fe3 127.0.0.1:8032 check
EOF

# Restart HAProxy
sudo systemctl restart haproxy
```

### 4.8 Best Practices và Troubleshooting

#### 4.8.1 Performance Best Practices
```sql
-- 1. Proper table design
-- ✅ DO: Use appropriate data types
CREATE TABLE optimized_table (
    id BIGINT,                    -- Use BIGINT for large IDs
    name VARCHAR(100),            -- Specify reasonable VARCHAR length
    amount DECIMAL(10,2),         -- Use DECIMAL for money
    created_date DATE,            -- Use DATE instead of DATETIME when time not needed
    updated_time DATETIME         -- Use DATETIME for precise timestamps
);

-- ❌ DON'T: Use oversized data types
CREATE TABLE bad_table (
    id VARCHAR(1000),             -- Wasteful for numeric IDs
    name TEXT,                    -- Overkill for short names
    amount DOUBLE,                -- Precision issues for money
    created_date VARCHAR(50)      -- String dates are inefficient
);

-- 2. Optimal partitioning
-- ✅ DO: Partition by frequently filtered columns
PARTITION BY RANGE(date_column) (
    PARTITION p20240101 VALUES LESS THAN ("2024-02-01"),
    PARTITION p20240201 VALUES LESS THAN ("2024-03-01")
);

-- 3. Smart bucketing
-- ✅ DO: Choose high-cardinality columns for distribution
DISTRIBUTED BY HASH(user_id) BUCKETS 32;  -- Good for user data

-- ❌ DON'T: Use low-cardinality columns
DISTRIBUTED BY HASH(status) BUCKETS 32;   -- Bad: only few status values
```

#### 4.8.2 Common Issues và Solutions
```bash
# Issue 1: High memory usage
# Solution: Tune JVM settings
cat > fe-jvm.conf << 'EOF'
-Xmx8g
-Xms8g
-XX:+UseG1GC
-XX:MaxGCPauseMillis=200
-XX:+PrintGCDetails
-XX:+PrintGCTimeStamps
-XX:+PrintGCApplicationStoppedTime
EOF

# Issue 2: Slow queries
# Solution: Enable query profiling
mysql -h 127.0.0.1 -P 9030 -u root -e "SET enable_profile=true;"

# Issue 3: Disk space issues
# Solution: Automated cleanup script
cat > cleanup-doris.sh << 'EOF'
#!/bin/bash

# Clean old partitions
mysql -h 127.0.0.1 -P 9030 -u root -e "
ALTER TABLE inventory_realtime DROP PARTITION p20231201;
"

# Compact tablets
mysql -h 127.0.0.1 -P 9030 -u root -e "
ADMIN SET FRONTEND CONFIG ('tablet_checker_interval_ms' = '1000');
"

# Clean logs
find ~/doris-docker/logs -name "*.log" -mtime +7 -delete
EOF
```

#### 4.8.3 Monitoring Dashboard Setup
```bash
# Tạo simple monitoring với Grafana
cat > docker-compose-monitoring.yml << 'EOF'
version: '3.8'

services:
  prometheus:
    image: prom/prometheus:latest
    container_name: prometheus
    ports:
      - "9090:9090"
    volumes:
      - ./prometheus.yml:/etc/prometheus/prometheus.yml
    networks:
      - doris-network

  grafana:
    image: grafana/grafana:latest
    container_name: grafana
    ports:
      - "3000:3000"
    environment:
      - GF_SECURITY_ADMIN_PASSWORD=admin
    networks:
      - doris-network

networks:
  doris-network:
    external: true
EOF

# Prometheus config
cat > prometheus.yml << 'EOF'
global:
  scrape_interval: 15s

scrape_configs:
  - job_name: 'doris-fe'
    static_configs:
      - targets: ['doris-fe:8030']

  - job_name: 'doris-be'
    static_configs:
      - targets: ['doris-be:8040']
EOF
```

#### 4.8.4 Security Hardening
```sql
-- 1. Create dedicated users
CREATE USER 'inventory_user'@'%' IDENTIFIED BY 'strong_password';
GRANT SELECT, INSERT, UPDATE ON inventory_db.* TO 'inventory_user'@'%';

CREATE USER 'traffic_user'@'%' IDENTIFIED BY 'another_strong_password';
GRANT SELECT, INSERT ON traffic_db.* TO 'traffic_user'@'%';

-- 2. Create read-only user for analytics
CREATE USER 'analytics_readonly'@'%' IDENTIFIED BY 'readonly_password';
GRANT SELECT ON *.* TO 'analytics_readonly'@'%';

-- 3. Disable root remote access (production)
UPDATE mysql.user SET Host='localhost' WHERE User='root';
FLUSH PRIVILEGES;
```

### 4.9 Production Deployment Checklist

#### 4.9.1 Pre-deployment Checklist
```bash
# Tạo deployment checklist
cat > deployment-checklist.md << 'EOF'
# Doris Production Deployment Checklist

## Infrastructure
- [ ] Sufficient hardware resources (CPU, Memory, Storage)
- [ ] Network connectivity between nodes
- [ ] Firewall rules configured
- [ ] DNS resolution working
- [ ] NTP synchronization enabled

## Security
- [ ] Strong passwords for all users
- [ ] SSL/TLS certificates configured
- [ ] Network encryption enabled
- [ ] Access control lists configured
- [ ] Audit logging enabled

## High Availability
- [ ] Multiple FE nodes (odd number, minimum 3)
- [ ] Multiple BE nodes (minimum 3)
- [ ] Load balancer configured
- [ ] Backup strategy implemented
- [ ] Disaster recovery plan documented

## Monitoring
- [ ] Health check endpoints configured
- [ ] Metrics collection setup
- [ ] Alerting rules defined
- [ ] Log aggregation configured
- [ ] Performance baselines established

## Testing
- [ ] Functional tests passed
- [ ] Performance tests completed
- [ ] Failover tests successful
- [ ] Backup/restore tests verified
- [ ] Security tests conducted
EOF
```

#### 4.9.2 Go-Live Script
```bash
# Tạo go-live automation script
cat > go-live.sh << 'EOF'
#!/bin/bash

echo "=== Doris Production Go-Live ==="

# 1. Final health check
echo "1. Performing final health check..."
./check-doris-health.sh

# 2. Create production databases
echo "2. Creating production databases..."
mysql -h 127.0.0.1 -P 9030 -u root < production-schema.sql

# 3. Start data ingestion
echo "3. Starting data ingestion..."
# Start Kafka consumers, routine loads, etc.

# 4. Enable monitoring
echo "4. Enabling monitoring..."
docker-compose -f docker-compose-monitoring.yml up -d

# 5. Final verification
echo "5. Final verification..."
sleep 30
./monitor-doris.sh

echo "=== Go-Live Complete ==="
echo "Access points:"
echo "- MySQL: localhost:9030"
echo "- Web UI: http://localhost:8030"
echo "- Grafana: http://localhost:3000 (admin/admin)"
EOF

chmod +x go-live.sh
```

## 5. Tiềm Năng của Apache Doris trong Big Data

### 5.1 Xu Hướng Thị Trường
- **Real-time Analytics**: Nhu cầu phân tích real-time tăng 40% hàng năm
- **Cloud-Native**: Hỗ trợ deployment trên Kubernetes và cloud platforms
- **AI/ML Integration**: Tích hợp với các framework ML phổ biến
- **Edge Computing**: Mở rộng khả năng xử lý tại edge devices

### 5.2 Lợi Thế Cạnh Tranh
- **Cost-Effective**: Giảm 50-70% chi phí so với các giải pháp thương mại
- **Simplified Architecture**: Giảm complexity của data stack
- **High Performance**: Sub-second query response cho TB-scale data
- **Active Community**: Cộng đồng phát triển mạnh mẽ và hỗ trợ tích cực

### 5.3 Roadmap Phát Triển
- **Multi-Model Support**: Hỗ trợ graph, document, time-series data
- **Serverless Computing**: Auto-scaling và pay-per-use model
- **Advanced Analytics**: Built-in ML algorithms và statistical functions
- **Global Distribution**: Multi-region replication và disaster recovery

### 5.4 Thách Thức và Giải Pháp
**Thách Thức:**
- Learning curve cho team mới
- Migration từ hệ thống legacy
- Monitoring và troubleshooting

**Giải Pháp:**
- Training programs và documentation chi tiết
- Migration tools và best practices
- Comprehensive monitoring stack (Prometheus, Grafana)

## Phân Tích Chi Tiết và Đề Xuất Ứng Dụng

### Đề Xuất 1: Hệ Thống Quản Lý Hàng Tồn Kho Thông Minh

#### Phân Tích Tình Hình Hiện Tại
Trong bối cảnh thương mại điện tử phát triển mạnh tại Việt Nam, các doanh nghiệp đang đối mặt với những thách thức:
- **Đa kênh bán hàng**: Online, offline, marketplace (Shopee, Lazada, Tiki)
- **Biến động nhu cầu**: Seasonal trends, flash sales, promotional campaigns
- **Chi phí lưu kho cao**: 20-30% tổng chi phí logistics
- **Thiếu visibility**: Không thể theo dõi tồn kho real-time across channels

#### Kiến Trúc Giải Pháp Đề Xuất
```
┌─────────────────┐    ┌──────────────┐    ┌─────────────────┐
│   Data Sources  │    │   Streaming  │    │  Apache Doris   │
│                 │    │   Pipeline   │    │                 │
│ • POS Systems   │───▶│   • Kafka    │───▶│ • Real-time     │
│ • E-commerce    │    │   • Flink    │    │   Analytics     │
│ • WMS          │    │   • CDC      │    │ • ML Predictions│
│ • ERP Systems   │    │              │    │ • Dashboards    │
└─────────────────┘    └──────────────┘    └─────────────────┘
                                                    │
                                           ┌─────────────────┐
                                           │   Applications  │
                                           │                 │
                                           │ • BI Dashboard  │
                                           │ • Mobile Apps   │
                                           │ • Alert System │
                                           │ • API Gateway   │
                                           └─────────────────┘
```

#### Implementation Roadmap
**Phase 1 (Tháng 1-2): Foundation Setup**
- Cài đặt Apache Doris cluster (3 FE + 6 BE nodes)
- Thiết lập data pipeline từ các nguồn chính
- Tạo data model cho inventory tracking

**Phase 2 (Tháng 3-4): Real-time Analytics**
- Implement stream processing cho real-time updates
- Xây dựng dashboard monitoring tồn kho
- Tích hợp alerting system

**Phase 3 (Tháng 5-6): Advanced Features**
- ML models cho demand forecasting
- Automated reordering system
- Cross-channel inventory optimization

#### ROI Dự Kiến
- **Giảm chi phí lưu kho**: 20-25% trong năm đầu
- **Tăng doanh thu**: 10-15% nhờ tránh tình trạng hết hàng
- **Cải thiện customer satisfaction**: 30% giảm complaints về out-of-stock
- **Payback period**: 8-12 tháng

### Đề Xuất 2: Hệ Thống Giám Sát Giao Thông Thông Minh TP.HCM

#### Phân Tích Bối Cảnh
TP.HCM đang đối mặt với những thách thức giao thông nghiêm trọng:
- **Mật độ giao thông cao**: 8 triệu xe máy, 800,000 ô tô
- **Ùn tắc thường xuyên**: Trung bình 2-3 giờ/ngày trong rush hours
- **Thiếu dữ liệu real-time**: Hệ thống giám sát hiện tại chưa tối ưu
- **Chi phí kinh tế**: Mất 1.2 tỷ USD/năm do ùn tắc giao thông

#### Kiến Trúc Hệ Thống Đề Xuất
```
┌─────────────────────────────────────────────────────────────┐
│                    Data Collection Layer                    │
├─────────────────┬─────────────────┬─────────────────────────┤
│ Traffic Cameras │ IoT Sensors     │ Mobile GPS Data         │
│ • 2000+ cameras │ • Speed sensors │ • Grab/Be drivers       │
│ • AI detection  │ • Volume count  │ • Private vehicles      │
│ • License plate │ • Weather data  │ • Public transport      │
└─────────────────┴─────────────────┴─────────────────────────┘
                              │
                    ┌─────────────────┐
                    │ Edge Computing  │
                    │ • Data filtering│
                    │ • Preprocessing │
                    │ • Compression   │
                    └─────────────────┘
                              │
                    ┌─────────────────┐
                    │ Message Queue   │
                    │ • Apache Kafka  │
                    │ • MQTT Broker   │
                    │ • Load Balancer │
                    └─────────────────┘
                              │
┌─────────────────────────────────────────────────────────────┐
│                    Apache Doris Cluster                     │
├─────────────────┬─────────────────┬─────────────────────────┤
│ Real-time       │ Historical      │ ML/Analytics            │
│ Processing      │ Data Store      │ Engine                  │
│ • Stream load   │ • Time-series   │ • Traffic prediction    │
│ • Aggregation   │ • Partitioning  │ • Route optimization    │
│ • Alerting      │ • Compression   │ • Anomaly detection     │
└─────────────────┴─────────────────┴─────────────────────────┘
                              │
┌─────────────────────────────────────────────────────────────┐
│                    Application Layer                        │
├─────────────────┬─────────────────┬─────────────────────────┤
│ Traffic Control │ Public Apps     │ Emergency Response      │
│ • Smart signals │ • Route planner │ • Incident detection    │
│ • Dynamic signs │ • Real-time map │ • Resource dispatch     │
│ • Coordination  │ • Public alerts │ • Recovery planning     │
└─────────────────┴─────────────────┴─────────────────────────┘
```

#### Tính Năng Chính
**1. Real-time Traffic Monitoring**
- Xử lý 10M+ events/second từ sensors và cameras
- Cập nhật traffic conditions mỗi 30 giây
- Phát hiện incidents trong vòng 2-3 phút

**2. Predictive Analytics**
- Dự báo ùn tắc trước 15-30 phút
- Phân tích pattern giao thông theo giờ/ngày/mùa
- Tối ưu hóa timing đèn giao thông

**3. Smart Route Optimization**
- Đề xuất tuyến đường tối ưu real-time
- Tích hợp với navigation apps
- Load balancing across road networks

**4. Emergency Response**
- Tự động phát hiện tai nạn qua AI
- Điều phối xe cứu thương/cảnh sát
- Tạo green corridors cho emergency vehicles

#### Implementation Plan
**Phase 1 (6 tháng đầu): Pilot Project**
- Triển khai tại 5 tuyến đường chính (Nguyễn Huệ, Lê Lợi, Điện Biên Phủ, etc.)
- 200 cameras + 500 IoT sensors
- Basic real-time monitoring dashboard

**Phase 2 (6-12 tháng): City-wide Expansion**
- Mở rộng ra 50 tuyến đường chính
- 1000+ cameras + 2000+ sensors
- Predictive analytics và smart routing

**Phase 3 (12-18 tháng): Advanced Features**
- AI-powered incident detection
- Integration với public transport
- Citizen engagement apps

#### Lợi Ích Dự Kiến
**Kinh Tế:**
- Giảm 25-30% thời gian di chuyển trong rush hours
- Tiết kiệm 300-400 triệu USD/năm từ reduced congestion
- Tăng 15-20% hiệu quả logistics và delivery

**Xã Hội:**
- Giảm 40% tai nạn giao thông
- Cải thiện chất lượng không khí (giảm 20% emissions)
- Tăng satisfaction của người dân về giao thông công cộng

**Môi Trường:**
- Giảm 25% fuel consumption
- Tối ưu hóa traffic flow giảm carbon footprint
- Hỗ trợ green transportation initiatives

### So Sánh và Khuyến Nghị

#### Độ Phức Tạp Triển Khai
| Tiêu Chí | Quản Lý Tồn Kho | Giám Sát Giao Thông |
|----------|------------------|---------------------|
| **Technical Complexity** | Trung bình | Cao |
| **Data Volume** | 1-10M events/day | 100M+ events/day |
| **Stakeholders** | Internal teams | Government, citizens |
| **Investment Required** | $100K-500K | $5M-20M |
| **Timeline** | 6-12 tháng | 18-24 tháng |

#### Khuyến Nghị Ưu Tiên
**Đề xuất bắt đầu với Hệ thống Quản lý Tồn kho** vì:
1. **Lower barrier to entry**: Ít stakeholders, easier approval process
2. **Faster ROI**: Có thể thấy kết quả trong 3-6 tháng
3. **Learning opportunity**: Xây dựng expertise với Apache Doris
4. **Scalable foundation**: Kinh nghiệm có thể apply cho traffic project

**Roadmap tổng thể:**
- **Year 1**: Focus on inventory management system
- **Year 2**: Leverage experience để pilot traffic monitoring
- **Year 3**: Scale traffic system city-wide

## Kết Luận

Apache Doris đại diện cho thế hệ mới của các hệ thống phân tích dữ liệu, kết hợp hiệu suất cao với tính đơn giản trong triển khai. Với khả năng xử lý real-time và chi phí thấp, Doris là lựa chọn lý tưởng cho các doanh nghiệp muốn hiện đại hóa hạ tầng dữ liệu của mình.

Đối với các ứng dụng cụ thể như quản lý tồn kho và giám sát giao thông tại TP.HCM, Apache Doris cung cấp nền tảng vững chắc để xây dựng các giải pháp thông minh, có khả năng mở rộng và đáp ứng nhu cầu thời gian thực của thành phố hiện đại.

**Khuyến nghị cuối cùng**: Bắt đầu với dự án quản lý tồn kho để tích lũy kinh nghiệm, sau đó mở rộng sang giám sát giao thông khi đã có foundation vững chắc về technical expertise và proven ROI.
