#ifndef FILE_XOR_MOD_HPP
#define FILE_XOR_MOD_HPP
#include <QDebug>
#include <QString>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#define FILE_PERMS QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ReadUser | QFileDevice::WriteUser | QFileDevice::ReadGroup | QFileDevice::WriteGroup | QFileDevice::ReadOther | QFileDevice::WriteOther
class file_xor_mod
{
    enum {max_file_length = 8192};      //stdio.h constant
    enum {max_counter_val = 9};
    enum {txt_suffix_len = 4};
    enum {max_path_len = 512};
    QString file_name;
    int delete_input_files_flag;
    QString path;                   //path to store a resulting file
    QString actions_if_res_file_exsist; //M- modification, R - rewrite
    int seconds;
    int poll_seconds;
    qint64 eight_byte_variable;
    QString buffer;
    void open_file(QFile& f, QIODeviceBase::OpenMode mode);
    void open_file(QFile& f, QIODeviceBase::OpenMode mode, QFileDevice::Permissions permissions);
    void read_from_file(QFile* f, QString& buf, qint64 len);
    void delete_file(QFile& f, const QString& path);
    QString search_duplicates(const QString& fname);
    void store_resulting_file(const QString& p);
    void store_resulting_file_timer(const QString& p);
    void modify_buffer();
public:
    void set_file_name(const QString& file_ext);
    void set_delete_input_files_flag(int flag);
    void set_path(const QString& ppath);
    void set_action(const QString& act);
    void set_timer(int sec);
    void set_poll_timer(int p_sec);
    void set_variable(const QString& v);
    int get_poll_seconds()
    {
        return poll_seconds;
    }
    void rrun();
};
#endif // FILE_XOR_MOD_HPP
