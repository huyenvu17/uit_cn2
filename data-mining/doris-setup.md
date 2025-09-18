# Hướng Dẫn Cài Đặt Apache Doris

## Mục Lục
1. [Thiết Lập Môi Trường](#thiết-lập-môi-trường)
2. [Cấu Hình Hệ Thống](#cấu-hình-hệ-thống)
3. [Cài Đặt Apache Doris](#cài-đặt-apache-doris)
4. [Cấu Hình và Khởi Động](#cấu-hình-và-khởi-động)
5. [Kiểm Tra Hoạt Động](#kiểm-tra-hoạt-động)
6. [Thiết Lập Bảo Mật](#thiết-lập-bảo-mật)

## Thiết Lập Môi Trường

### 1. Cập Nhật Hệ Thống
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Cài Đặt Java
```bash
# Cài đặt OpenJDK 17
sudo apt install openjdk-17-jdk -y

# Kiểm tra phiên bản Java
java -version

# Thiết lập JAVA_HOME
export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64
echo 'export JAVA_HOME=/usr/lib/jvm/java-17-openjdk-amd64' >> ~/.bashrc
source ~/.bashrc
```

### 3. Cài Đặt Gói Phụ Thuộc
```bash
sudo apt install build-essential maven cmake byacc flex automake \
    libtool-bin bison binutils-dev libiberty-dev zip unzip \
    libncurses5-dev curl git ninja-build python3 -y
```

## Cấu Hình Hệ Thống

### 1. Cấu Hình File Limits
sudo vi /etc/security/limits.conf

# Thêm vào file limits.conf
* soft nofile 1000000
* hard nofile 1000000


### 2. Cấu Hình Bộ Nhớ Ảo
sudo vi /etc/sysctl.conf

# Thêm vào file sysctl.conf
vm.max_map_count = 2000000

# Áp dụng cấu hình
sudo sysctl -p

# Tắt swap
sudo swapoff -a
```

## Cài Đặt Apache Doris

### 1. Tải và Giải Nén
```bash
cd ~
wget https://apache-doris-releases.oss-accelerate.aliyuncs.com/apache-doris-3.0.7-bin-x64.tar.gz
tar -zxvf apache-doris-3.0.7-bin-x64.tar.gz
mv apache-doris-3.0.7-bin-x64 apache-doris
cd apache-doris
```

## Cấu Hình và Khởi Động

### 1. Cấu Hình Frontend (FE)
```bash
# Tạo thư mục metadata
mkdir -p fe/doris-meta

# Cấu hình FE
vi fe/conf/fe.conf

# cập nhật
priority_networks = 127.0.0.1/24
meta_dir=${DORIS_HOME}/doris-meta

# Khởi động FE
cd fe
./bin/start_fe.sh --daemon
```

### 2. Cấu Hình Backend (BE)
```bash
# Tạo thư mục storage
mkdir -p be/storage
chmod 755 be/storage

# Cấu hình BE
vi be/conf/be.conf

# cập nhật
priority_networks = 127.0.0.1/24
storage_root_path =${DORIS_HOME}/storage

# Khởi động BE
cd be
./bin/start_be.sh --daemon
```

## Kiểm Tra Hoạt Động

### 1. Cài Đặt MySQL Client
```bash
sudo apt install mysql-client -y
```

### 2. Kiểm Tra Cụm
```sql
-- Kết nối với Doris
mysql -uroot -P9030 -h 127.0.0.1

-- Kiểm tra trạng thái FE
SHOW FRONTENDS;

-- Đăng ký BE
ALTER SYSTEM ADD BACKEND "127.0.0.1:9050";

-- Kiểm tra trạng thái BE
SHOW BACKENDS;
```

## Thiết Lập Bảo Mật

### 1. Truy Cập Giao Diện Web
- URL: http://localhost:8030
- Tài khoản mặc định:
  - Tên đăng nhập: `root`
  - Mật khẩu: (để trống)

### 2. Thiết Lập Mật Khẩu (tùy chọn)
```sql
-- Đặt mật khẩu cho tài khoản root và admin
SET PASSWORD FOR 'root' = PASSWORD('mật-khẩu-root');
SET PASSWORD FOR 'admin' = PASSWORD('mật-khẩu-admin');
```

## Test

```sql
CREATE DATABASE demo;
USE demo;
CREATE TABLE mytable (
  k1 TINYINT,
  k2 DECIMAL(10, 2) DEFAULT "10.05",
  k3 CHAR(10) COMMENT "string column",
  k4 INT NOT NULL DEFAULT "1" COMMENT "int column"
) COMMENT "my first table"
DISTRIBUTED BY HASH(k1) BUCKETS 1
PROPERTIES ('replication_num' = '1');
```

## Nạp dữ liệu thông qua Stream Load
curl --location-trusted -u root: -T ~/data.csv -H "column_separator:," http://127.0.0.1:8030/api/demo/mytable/_stream_loads


==============================
Khởi động Spark Standalone
$SPARK_HOME/sbin/start-all.sh

PYSPARK
$SPARK_HOME/bin/pyspark