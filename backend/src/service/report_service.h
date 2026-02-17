#ifndef SERVICE_REPORT_SERVICE_H
#define SERVICE_REPORT_SERVICE_H

#include "auth_service.h"
#include "../domain/models.h"
#include "../repository/report_repository.h"

#include <string>

// 利润表服务：负责按确认口径计算利润结果
class ReportService {
public:
    ReportService(AuthService &authService, ReportRepository &reportRepository);

    bool getMonthlyProfitStatement(int userId,
                                   int companyId,
                                   const std::string &periodMonth,
                                   ProfitStatementResult &outResult,
                                   std::string &outReasonNote,
                                   std::string &errorMessage) const;

    bool upsertMonthlyRecord(int userId,
                             const MonthlyReportRecord &record,
                             std::string &errorMessage);

private:
    ProfitStatementResult calculateProfit(const MonthlyReportRecord &record) const;

    AuthService &authService;
    ReportRepository &reportRepository;
};

#endif
