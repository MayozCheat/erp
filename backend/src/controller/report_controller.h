#ifndef CONTROLLER_REPORT_CONTROLLER_H
#define CONTROLLER_REPORT_CONTROLLER_H

#include "../service/report_service.h"

#include <string>

// 报表控制器：负责参数组装与响应输出
class ReportController {
public:
    explicit ReportController(ReportService &reportService);

    std::string getMonthlyProfit(int userId, int companyId, const std::string &periodMonth) const;
    std::string upsertMonthlyData(int userId, const MonthlyReportRecord &record);

private:
    ReportService &reportService;
};

#endif
