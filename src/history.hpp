#pragma once

#include <string>
#include <vector>

struct HistoryEntry {
    std::string expression;
    std::string result;
};

class HistoryStore {
public:
    explicit HistoryStore(std::string path, std::size_t limit = 100);

    void load();
    void save() const;
    void add(std::string expression, std::string result);
    void clear();

    const std::vector<HistoryEntry>& entries() const;

private:
    std::string path_;
    std::size_t limit_;
    std::vector<HistoryEntry> entries_;
};
