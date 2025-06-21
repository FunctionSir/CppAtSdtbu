#include "comms.hpp"
#include "commentry.hpp"
#include <stdexcept>
std::istream &operator>>(istream &is, Comms &comms) {
    int cnt;
    CommEntry tmp;
    is >> cnt;
    while (cnt--) {
        is >> tmp;
        comms.m_entries.push_back(tmp);
        comms.m_logger.LogChange(comms, comms.m_entries.size() - 1, "NEW");
    }
    return is;
}
std::ostream &operator<<(ostream &os, const Comms &comms) {
    os << "条目总数: " << comms.m_entries.size() << "\n";
    for (const auto &e : comms.m_entries) {
        os << e << "\n";
    }
    return os;
}

void Logger::LogChange(Comms &ce, size_t idx, string type) {
    m_cnt++;
    m_ofs << "#" << m_cnt << " [" << type << "]" << " @" << idx << " -> " << ce.m_entries[idx] << endl;
}
void Logger::LogChange(CommEntry &ce, size_t idx, string type) {
    m_cnt++;
    m_ofs << "#" << m_cnt << " [" << type << "]" << " @" << idx << " ! " << ce << endl;
}
Logger::Logger(string path) {
    m_cnt = 0;
    m_path = path;
    m_ofs.close();
    m_ofs.clear();
    m_ofs.open(m_path);
}
Logger::Logger() {
    m_cnt = 0;
    m_path = "comms.log";
    m_ofs.close();
    m_ofs.clear();
    m_ofs.open(m_path);
}
void Logger::SetLogger(string path) {
    m_cnt = 0;
    m_path = path;
    m_ofs.close();
    m_ofs.clear();
    m_ofs.open(m_path);
    if (!m_ofs.good()) {
        throw runtime_error("log file not good");
    }
}
Comms::Comms(string loggerPath) {
    m_logger.SetLogger(loggerPath);
}
Comms::Comms() {
    m_logger.SetLogger("comms.log");
}
void Comms::NewEntry(void) {
    CommEntry tmp;
    cout << "请输入用空格分开的姓名和电话: ";
    cin >> tmp;
    m_entries.push_back(tmp);
    m_logger.LogChange(*this, m_entries.size() - 1, "NEW");
}
void Comms::ModEntry() {
    size_t idx;
    cout << "输入要修改的条目的索引: ";
    cin >> idx;
    m_logger.LogChange(m_entries[idx], idx, "MOD");
    cout << "请输入用空格分开的姓名和电话: ";
    cin >> m_entries[idx];
    m_logger.LogChange(*this, idx, "MOD");
}
void Comms::DelEntry() {
    size_t idx;
    cout << "输入要删除的条目的索引: ";
    cin >> idx;
    m_logger.LogChange(m_entries[idx], idx, "DEL");
    m_entries.erase(m_entries.begin() + long(idx));
}
Logger::~Logger() {
    m_ofs.flush();
    m_ofs.close();
}
void Logger::LogRaw(string s) {
    m_ofs << s;
    m_ofs.flush();
}
