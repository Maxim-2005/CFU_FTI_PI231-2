Student make_student(const std::string& line)
{
    std::size_t delimiter_pos = line.find(';');
    std::string name = line.substr(0, delimiter_pos);
    std::string group = line.substr(delimiter_pos + 1);
    return {name, group};
}

bool is_upper(const Student& s1, const Student& s2)
{
    if (s1.group != s2.group)
        return s1.group < s2.group;
    
    return s1.name < s2.name;
}

void print(const std::vector<Student>& students)
{
    if (students.empty()) {
        std::cout << "Empty list!" << std::endl;
        return;
    }
    
    std::string current_group = students[0].group;
    std::cout << current_group << std::endl;
    
    for (const auto& student : students) {
        if (student.group != current_group) {
            current_group = student.group;
            std::cout << current_group << std::endl;
        }
        std::cout << "- " << student.name << std::endl;
    }
}