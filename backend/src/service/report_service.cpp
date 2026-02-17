#include "report_service.h"

ReportService::ReportService(AuthService &authService, ReportRepository &reportRepository)
    : authService(authService), reportRepository(reportRepository) {}

bool ReportService::getMonthlyProfitStatement(int userId,
                                              int companyId,
                                              const std::string &periodMonth,
                                              ProfitStatementResult &outResult,
                                              std::string &outReasonNote,
                                              std::string &errorMessage) const {
    // 读取权限校验
    if (!authService.checkCompanyReadPermission(userId, companyId, errorMessage)) {
        return false;
    }

    auto recordOptional = reportRepository.findMonthlyRecord(companyId, periodMonth);
    if (!recordOptional.has_value()) {
        errorMessage = "未找到该公司该月份数据";
        return false;
    }

    outResult = calculateProfit(recordOptional.value());
    outReasonNote = recordOptional->reasonNote;
    return true;
}

bool ReportService::upsertMonthlyRecord(int userId,
                                        const MonthlyReportRecord &record,
                                        std::string &errorMessage) {
    // 写入权限校验
    if (!authService.checkCompanyWritePermission(userId, record.companyId, errorMessage)) {
        return false;
    }

    if (record.periodMonth.size() != 7 || record.periodMonth[4] != '-') {
        errorMessage = "期间格式错误，应为 YYYY-MM";
        return false;
    }

    reportRepository.saveOrUpdateRecord(record);
    return true;
}

ProfitStatementResult ReportService::calculateProfit(const MonthlyReportRecord &record) const {
    ProfitStatementResult result{};

    // 已确认口径：
    // 1) 财务费用纳入考核
    // 2) 非正常支出影响利润
    // 3) 其他营业外收入/支出不纳入考核（此最小版本以 totalProfit 演示账面链路，可在 V2 增加双口径并行）
    result.operatingProfit = record.revenue - record.cost - record.financeExpense;

    // 非正常支出计入利润
    result.totalProfit = result.operatingProfit - record.abnormalExpense;

    // 固定税率 25%，若利润为负则税额为0
    result.incomeTax = result.totalProfit > 0 ? result.totalProfit * 0.25 : 0.0;
    result.netProfit = result.totalProfit - result.incomeTax;
    return result;
}
