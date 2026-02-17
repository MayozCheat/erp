# DEVELOPMENT_PLAYBOOK（开发与调试手册）

## 1. 环境准备
- 操作系统：Linux（建议）
- 编译器：g++（支持 C++17 或以上）
- 数据库：MySQL 8.x
- 构建方式：Makefile

## 2. 目录约定（示例）
- backend/src/controller
- backend/src/service
- backend/src/repository
- backend/src/domain
- backend/src/utils

## 3. 编译步骤（示例）
```bash
cd backend
make clean
make
