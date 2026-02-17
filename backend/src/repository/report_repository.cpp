#include "report_repository.h"

ReportRepository::ReportRepository() {
    records.push_back({1001, "2025-01", 1200000.0, 800000.0, 50000.0, 10000.0, 15000.0, 8000.0, "项目A一次性整改支出"});
}

std::optional<MonthlyReportRecord> ReportRepository::findMonthlyRecord(int companyId, const std::string &periodMonth) const {
    for (const auto &record : records) {
        if (record.companyId == companyId && record.periodMonth == periodMonth) {
            return record;
        }
    }
    return std::nullopt;
}

bool ReportRepository::saveOrUpdateRecord(const MonthlyReportRecord &record) {
    for (auto &item : records) {
        if (item.companyId == record.companyId && item.periodMonth == record.periodMonth) {
            item = record;
            return true;
        }
    }
    records.push_back(record);
    return true;
}
