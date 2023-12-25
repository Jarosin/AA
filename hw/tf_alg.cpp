in_file - название исходного файла           // -3
out_file - название результирующего файла    // -2
substr - искомая подстрока                   // -1


void substr_search_pos(std::string &in_file, std::string &out_file, std::string &substr)
{
    std::ifstream in(in_file, std::ios::in);    // 1
    if (!in.is_open())                          // 2
    {
        return;                                 // 3
    }
    std::ofstream out(out_file);                // 4
    if (!out.is_open())                         // 5
    {
        return;                                 // 6
    }
    std::string line;                           // 7
    size_t pos;                                 // 8
    int i = 0;                                  // 9
    while (getline(in, line)){                  // 10
        pos = line.find(substr);                // 11
        while (pos != std::string::npos)        // 12
        {
            out << i + 1 << " " << pos << "\n"; // 13
            pos = line.find(substr, pos + 1);   // 14
            i++;                                // 15
        }
    }
    in.close();                                 // 16
    out.close();                                // 17
}
