#ifndef REPOSITORY_REPORT_REPOSITORY_H
#define REPOSITORY_REPORT_REPOSITORY_H

#include "../domain/models.h"

#include <optional>
#include <vector>

// 报表仓储：负责月度报表数据持久化（演示内存实现）
class ReportRepository {
public:
    ReportRepository();

    std::optional<MonthlyReportRecord> findMonthlyRecord(int companyId, const std::string &periodMonth) const;
    bool saveOrUpdateRecord(const MonthlyReportRecord &record);

private:
    std::vector<MonthlyReportRecord> records;
};

#endif
