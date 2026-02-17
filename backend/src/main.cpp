#include "controller/auth_controller.h"
#include "controller/report_controller.h"
#include "repository/report_repository.h"
#include "repository/user_repository.h"
#include "service/auth_service.h"
#include "service/report_service.h"

#include <iostream>

// 最小可运行示例：
// 1) 登录
// 2) 查询月度利润
// 3) 修改月度数据
int main() {
    UserRepository userRepository;
    ReportRepository reportRepository;

    AuthService authService(userRepository);
    ReportService reportService(authService, reportRepository);

    AuthController authController(authService);
    ReportController reportController(reportService);

    std::cout << "=== 登录演示 ===" << std::endl;
    std::cout << authController.login("finance_a", "finance123") << std::endl;

    std::cout << "\n=== 查询 1001 公司 2025-01 月报 ===" << std::endl;
    std::cout << reportController.getMonthlyProfit(2, 1001, "2025-01") << std::endl;

    std::cout << "\n=== 尝试写入只读公司 1002（应失败） ===" << std::endl;
    MonthlyReportRecord deniedRecord{1002, "2025-01", 300000, 200000, 12000, 0, 0, 3000, "手工备注"};
    std::cout << reportController.upsertMonthlyData(2, deniedRecord) << std::endl;

    std::cout << "\n=== 写入可写公司 1001（应成功） ===" << std::endl;
    MonthlyReportRecord updateRecord{1001, "2025-02", 1300000, 810000, 52000, 0, 0, 9000, "手工补录：2月数据"};
    std::cout << reportController.upsertMonthlyData(2, updateRecord) << std::endl;

    std::cout << "\n=== 查询 1001 公司 2025-02 月报 ===" << std::endl;
    std::cout << reportController.getMonthlyProfit(2, 1001, "2025-02") << std::endl;

    return 0;
}
