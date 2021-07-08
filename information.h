#pragma once
#include <QString>
//作者注
const QString _author("AnglesD");//作者
const QString _email("dyy3688098qq@163.com");//邮箱
const QString _qq("1005562341");//QQ
const QString _date(__TIMESTAMP__);//日期
const QString _edition(APP_VERSION);//版本号
//更新记录
//1.0.0.1:程序初步完成
//1.0.1.4:添加数据查找功能，数据视图切换功能，程序结构优化
//1.0.2.1:完善学校、公司详细数据视窗
//1.0.2.3:修复打开筛选框闪退、修复详细数据视窗打开闪退
//BUG记录
//1.0.0.1 2020-11-23 操作:程序编译 问题:about版本信息、日期信息无法更新 原因:未知 处理:二次编译__TIMESTAMP__、APP_VERSION的信息
//1.0.0.1 2020-11-23 操作:mainwindow->tablewindow->筛选框 问题:打开筛选框触发闪退 原因:显示新信息时旧信息未处理 处理:m_model、m_items同步清理
//1.0.0.1 2020-11-27 操作:mainwindow->tablewindow->findwidget->关闭主窗口 问题:程序异常退出 原因:delete Filter 释放内存错误 处理:delete[] Filter
//1.0.1.4 2020-11-27 操作:mainwindow->tablewindow->切换数据视图、筛选框、排序 问题:数据表刷新为空白 原因:未知 处理:待处理
//1.0.2.1 2020-11-28 操作:mainwindow->tablewindow->切换数据视图->add 问题:程序异常退出 原因:school与company的add函数未定义 处理:已追加定义
//待完善功能
//数据输入正确性检测
//数据信息链接捆绑
//详细信息导出功能
//语言设置
