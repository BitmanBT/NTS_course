#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_mutex mtx;

struct Student
{
    uint64_t id;
    std::string name;
    uint32_t age;

    Student(const uint64_t _id, const std::string& _name, const uint32_t _age) :
        id(_id), name(_name), age(_age) { }
};

class StudentDatabase
{
public:
    void AddStudent(const uint64_t id, const std::string& name, const uint32_t age)
    {
        std::shared_ptr<Student> ptr(new Student(id, name, age));
        auto it = database.find(ptr.get()->id);
        if (it != database.end())
        {
            throw std::logic_error("Student already exists in database!");
        } else {
            database[ptr.get()->id] = ptr;
        }
    }

    void DeleteStudent(const uint64_t id)
    {
        auto it = database.find(id);
        if (it == database.end())
        {
            throw std::logic_error("Such student doesn't exist in database!");
        } else {
            database.erase(it);
        }
    }

    std::shared_ptr<Student> GetStudent(const uint64_t id)
    {
        auto it = database.find(id);
        if (it == database.end())
        {
            throw std::logic_error("Such student doesn't exist in database!");
        } else {
            return database[id];
        }
    }
private:
    std::unordered_map<uint64_t, std::shared_ptr<Student>> database;
};

void Reader(StudentDatabase& db, const uint64_t id)
{
    mtx.lock_shared();
    auto student = db.GetStudent(id);
    std::cout << "Student: " << student->name << ". Age: " << student->age << ".\n";
    mtx.unlock_shared();
}

void Writer(StudentDatabase& db, const uint64_t id, const std::string name, const uint32_t age)
{
    mtx.lock();
    db.AddStudent(id, name, age);
    mtx.unlock();
}

int main()
{
    StudentDatabase db;
    db.AddStudent(1, "Vanya", 21);
    db.AddStudent(2, "Vasya", 20);

    std::thread t_reader(Reader, std::ref(db), 2);
    std::thread t_writer(Writer, std::ref(db), 3, "Anya", 19);

    t_reader.join();
    t_writer.join();
}