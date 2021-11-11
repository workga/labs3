#ifndef __H_TEXT_PROCESSOR
#define __H_TEXT_PROCESSOR

#include <filesystem>
namespace fs = std::filesystem;

class TextProcessor {
public:
	TextProcessor() noexcept  : filled(false), sorted(false) {};
	TextProcessor(fs::path filename);
	TextProcessor(std::vector<std::pair<std::string, int>> v);

	~TextProcessor() = default;

	void list_files(fs::path dirname) const;
	void load_words(fs::path filename);
	void get_words(int min_len = 0, int num = 0) noexcept;

private:
	std::vector<std::pair<std::string, int>> words;
	bool filled;
	bool sorted;

	void clear_words() noexcept;

	void sort();
	int  cmp(std::pair<std::string, int> a, std::pair<std::string, int> b) const noexcept;
};

#endif // !__H_TEXT_PROCESSOR
