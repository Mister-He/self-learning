# include <stdio.h>
# include <iostream>    
# include <map>
# include "csv.h" //self written library
# include <sstream>
# include <fstream>
# include <iterator>
# include <algorithm>
# include <numeric>
# include <array>
using namespace std;

// Write a function to load smoking data from a csv file
map<string, vector<double>> readsmokingtable(const string path) {
    string filePath = "/Users/heyichen/Desktop/GitHub/DEMOS/data/";
    string filename = filePath + "smokingtable_" + path + "_1.csv";

    // Use csv.h to read the csv file
    io::CSVReader<9> reader(filename);

    // Colnames list
    reader.read_header(io::ignore_extra_column, "\"V1\"", "\"V2\"", "\"V3\"", "\"V4\"", "\"V5\"", "\"V6\"", "\"V7\"", "\"V8\"", "\"V9\"");

    // Define vector to store every column's data
    map<string, vector<double>> data;
    for (const auto& col : {"\"V1\"", "\"V2\"", "\"V3\"", "\"V4\"", "\"V5\"", "\"V6\"", "\"V7\"", "\"V8\"", "\"V9\""}) {
        data[col] = vector<double>();
    }

    // Read data in CSV file
    string V1, V2, V3, V4, V5, V6, V7, V8, V9;
    while (reader.read_row(V1,V2,V3,V4,V5,V6,V7,V8,V9)) {
        data["V1"].push_back(stod(V1));
        data["V2"].push_back(stod(V2));
        data["V3"].push_back(stod(V3));
        data["V4"].push_back(stod(V4));
        data["V5"].push_back(stod(V5));
        data["V6"].push_back(stod(V6));
        data["V7"].push_back(stod(V7));
        data["V8"].push_back(stod(V8));
        data["V9"].push_back(stod(V9));
    }

    return data;
}

std::map<std::string, std::vector<double>> readheightbmivarData() {
    std::string filePath = "/Users/heyichen/Desktop/GitHub/DEMOS/data";
    std::string filename = filePath + "/heightbmivar.csv";

    // 使用 csv-parser 库读取 CSV 文件
    io::CSVReader<7> reader(filename);
    reader.read_header(io::ignore_extra_column, "gender","ethnic","age_group","bmi_group","mean","sd","n_subjects");

    // 定义 vector 来存储每列的数据
    std::map<std::string, std::vector<double>> data;    

    // 初始化每列的 vector
    data["gender"] = std::vector<double>();
    data["ethnic"] = std::vector<double>();
    data["age_group"] = std::vector<double>();
    data["bmi_group"] = std::vector<double>();
    data["mean"] = std::vector<double>();
    data["sd"] = std::vector<double>();
    data["n_subjects"] = std::vector<double>();

    double gender,ethnic,age_group,bmi_group,mean,sd,n_subjects;

    // 读取每一行并将值放入对应的 vector
    while (reader.read_row(gender,ethnic,age_group,bmi_group,mean,sd,n_subjects)) {
        data["gender"].push_back(gender);
        data["ethnic"].push_back(ethnic);
        data["age_group"].push_back(age_group);
        data["bmi_group"].push_back(bmi_group);
        data["mean"].push_back(mean);
        data["sd"].push_back(sd);
        data["n_subjects"].push_back(n_subjects);
    }

    return data;
}

int main(){
    //const auto data = readheightbmivarData();

    // Go over chi, mal, ind and oth and read the data into different objects
    const auto data = readsmokingtable("chi_fem");
    //map<string,string> reference_list;
    //char gender = "male","";

    // 打印维度
    std::cout << "Data dimensions:" << std::endl;
    for (const auto& pair : data) {
        std::cout << pair.first << ": " << pair.second.size() << std::endl;
    }

    // 打印前六行数据
    std::cout << "\nFirst six rows of data:" << std::endl;
    for (const auto& pair : data) {
        std::cout << pair.first << ": ";
        for (size_t i = 0; i < std::min(pair.second.size(), size_t(6)); ++i) {
            std::cout << pair.second[i] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}