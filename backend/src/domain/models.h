#ifndef DOMAIN_MODELS_H
#define DOMAIN_MODELS_H

#include <string>
#include <unordered_map>
#include <vector>

// 用户公司权限级别
// READ_ONLY: 只读权限
// READ_WRITE: 可读可写权限
enum class CompanyPermissionLevel {
    READ_ONLY,
    READ_WRITE
};

// 系统用户领域模型
struct User {
    int userId;
    std::string username;
    std::string passwordHash;
    bool isAdmin;
};

// 用户对公司权限映射
struct UserCompanyPermission {
    int userId;
    int companyId;
    CompanyPermissionLevel level;
};

// 月度报表记录（最小可运行版本）
struct MonthlyReportRecord {
    int companyId;
    std::string periodMonth; // YYYY-MM
    double revenue;
    double cost;
    double financeExpense;
    double nonOperatingIncome;
    double nonOperatingExpense;
    double abnormalExpense;
    std::string reasonNote; // 原因说明：按需求仅手工填写
};

// 计算结果 DTO
struct ProfitStatementResult {
    double operatingProfit;
    double totalProfit;
    double incomeTax;
    double netProfit;
};

#endif
