//
// Created by ar on 22.03.20.
//

#ifndef PUZZLE_CINIFILE_H
#define PUZZLE_CINIFILE_H

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>

const std::string file="./config.ini";
#define MAX_PATH 255
inline std::string exe_directory(const std::string & filename)
{
    char directory[MAX_PATH] = { 0 };
    //GetModuleFileNameA(NULL, directory, MAX_PATH);
    strrchr(directory, '\\')[0] = '\0';

    return boost::filesystem::absolute(
            boost::filesystem::path(filename),
            boost::filesystem::path(directory)
    ).string();
}

class CIniFile
{
private:
    //
    std::string m_path=file;
	boost::property_tree::ptree m_data;

    CIniFile(const std::string & filename)
    {
        //m_path = exe_directory(filename);
        boost::property_tree::ini_parser::read_ini(filename, m_data);
    }
    static CIniFile * instance;

public:
	//

	~CIniFile()
	{
        write();
	}

	static CIniFile * getInstance(){
        if (! instance )
            instance = new CIniFile(file);
	    return instance;
	}

	//
	void write(const std::string & path="")
	{
        std::string save_path = (path.length() ? exe_directory(path) : m_path);
        boost::property_tree::ini_parser::write_ini(save_path, m_data);
	}

	//
	template <typename T>
	T get(const std::string & key)
	{
		return m_data.get<T>(key);
	}

	//
	template <typename T>
	void set(const std::string & key, const T & value){
        m_data.put(key, value);
        write();
	}
};

#endif //PUZZLE_CINIFILE_H
