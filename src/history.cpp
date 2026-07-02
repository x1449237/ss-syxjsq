#include "history.hpp"

#include <fstream>
#include <utility>

HistoryStore::HistoryStore(std::string path, std::size_t limit)
    : path_(std::move(path)), limit_(limit) {}

void HistoryStore::load() {
    entries_.clear();

    std::ifstream in(path_);
    if (!in) {
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        const std::size_t separator = line.find('\t');
        if (separator == std::string::npos) {
            continue;
        }
        add(line.substr(0, separator), line.substr(separator + 1));
    }
}

void HistoryStore::save() const {
    std::ofstream out(path_);
    if (!out) {
        return;
    }

    for (const HistoryEntry& entry : entries_) {
        out << entry.expression << '\t' << entry.result << '\n';
    }
}

void HistoryStore::add(std::string expression, std::string result) {
    entries_.push_back({std::move(expression), std::move(result)});
    while (entries_.size() > limit_) {
        entries_.erase(entries_.begin());
    }
}

void HistoryStore::clear() {
    entries_.clear();
}

const std::vector<HistoryEntry>& HistoryStore::entries() const {
    return entries_;
}
