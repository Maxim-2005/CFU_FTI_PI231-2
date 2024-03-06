bool compare(const std::string& a, const std::string& b) {
    int count_a = 0;
    int count_b = 0;
    
    // счетчики кол-ва едениц
    for (char c : a)
        if (c == '1')
            count_a++;
    
    for (char c : b)
        if (c == '1')
            count_b++;
    
    // сортировка и вывод
    if (count_a > count_b)
        return true;
    else if (count_a < count_b)
        return false;
    else if (count_a == count_b){
        if (a.length() > b.length())
            return false;
        else if (a.length() < b.length())
            return true;
        else if (a.length() == b.length()){
            if (a.find('0') >= b.find('0'))
                return false;
            else
                return true;
        }
    }
}