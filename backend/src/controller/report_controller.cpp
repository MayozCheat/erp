#include "report_controller.h"

#include <sstream>

ReportController::ReportController(ReportService &reportService) : reportService(reportService) {}

std::string ReportController::getMonthlyProfit(int userId, int companyId, const std::string &periodMonth) const {
    ProfitStatementResult result{};
    std::string reasonNote;
    std::string errorMessage;

    bool ok = reportService.getMonthlyProfitStatement(userId, companyId, periodMonth, result, reasonNote, errorMessage);
    if (!ok) {
        return "{\"success\":false,\"message\":\"" + errorMessage + "\"}";
    }

    std::ostringstream oss;
    oss << "{\"success\":true,\"data\":{"
        << "\"operatingProfit\":" << result.operatingProfit << ","
        << "\"totalProfit\":" << result.totalProfit << ","
        << "\"incomeTax\":" << result.incomeTax << ","
        << "\"netProfit\":" << result.netProfit << ","
        << "\"reasonNote\":\"" << reasonNote << "\"}}";
    return oss.str();
}

std::string ReportController::upsertMonthlyData(int userId, const MonthlyReportRecord &record) {
    std::string errorMessage;
    bool ok = reportService.upsertMonthlyRecord(userId, record, errorMessage);
    if (!ok) {
        return "{\"success\":false,\"message\":\"" + errorMessage + "\"}";
    }

    return "{\"success\":true,\"message\":\"月度数据保存成功\"}";
}
