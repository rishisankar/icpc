// result should be empty at first
// example: graphs/cantinaofbabel

void split(string s, string delim, vector<string>& result) {
    auto start = 0U;
    auto end = s.find(delim);
    while (end != string::npos)
    {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }

    result.push_back(s.substr(start, end));
}