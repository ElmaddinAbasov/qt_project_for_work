#include "file_xor_mod.hpp"

void file_xor_mod::open_file(QFile& f, QIODeviceBase::OpenMode mode)
{
    bool res;
    res = f.open(mode);
    if (!res)
    {
        qDebug() << "void file_xor_mod::open_file(QFile& f, QIODeviceBase::OpenMode mode)";
        exit(1);
    }
}

void file_xor_mod::open_file(QFile& f, QIODeviceBase::OpenMode mode, QFileDevice::Permissions permissions)
{
    bool res;
    res = f.open(mode, permissions);
    if (!res)
    {
        qDebug() << "void file_xor_mod::open_file(QFile& f, QIODeviceBase::OpenMode mode, QFileDevice::Permissions permissions)";
        exit(2);
    }
}

void file_xor_mod::read_from_file(QFile* f, QString& buf, qint64 len)
{
    QTextStream in(f);
    buf = in.read(len);
    qDebug() << buf;
}

void file_xor_mod::delete_file(QFile& f, const QString& path)
{
    bool res;
    res = f.remove(path);
    if (!res)
    {
        qDebug() << "void file_xor_mod::delete_file(QFile& f, const QString& path)";
        exit(3);
    }
}

void file_xor_mod::modify_buffer()
{
    qint64 val = 0;
    int i;
    for (i = 0; i < buffer.size(); i++)
    {
        if (buffer[i] == '\n' || buffer[i] == '\r')
            continue;
        val = (qint64)buffer[i].unicode() ^ eight_byte_variable;                 //rethink this one
//        if (val >= 0 && val >= 0x10FFFF)
        {
            qDebug() << "I`m here\n";
            quint32 c = (quint32)val;
            buffer[i] = QChar(c);
        }
    }
    qDebug() << "void file_xor_mod::modify_buffer()" << buffer;
}

QString file_xor_mod::search_duplicates(const QString& fname)
{
    QString s = fname.mid(0, fname.length() - txt_suffix_len);
    QString ss;
    int counter = 1;
    qDebug() << s;
    while (1)
    {
        ss = s + QChar('0' + counter);
        QFile f(ss + ".txt");
        qDebug() << ss + ".txt";
        if (f.exists(ss + ".txt") && counter <= max_counter_val)
        {
            counter++;
            continue;
        }
        break;
    }
    return ss + ".txt";
}

void file_xor_mod::store_resulting_file(const QString& p)
{
    QFile f(p);
    QTextStream out(&f);
    if (f.exists(p) && actions_if_res_file_exsist == "m")
    {
        QString new_path = search_duplicates(p);
        QFile f(new_path);
        QTextStream out(&f);
        open_file(f, QIODeviceBase::WriteOnly, FILE_PERMS);
        modify_buffer();
        out << buffer;
        f.close();
        return;
    }
    if (f.exists(p) && actions_if_res_file_exsist == "r")
    {
        open_file(f, QIODeviceBase::WriteOnly);
        QTextStream out(&f);
        modify_buffer();
        out << buffer;
        f.close();
        return;
    }
    open_file(f, QIODeviceBase::WriteOnly, FILE_PERMS);
    modify_buffer();
    out << buffer;
    f.close();
}

void file_xor_mod::store_resulting_file_timer(const QString& p)
{
    QFile f(p);
    QTextStream out(&f);
    clock_t start, end;
    if (f.exists(p) && actions_if_res_file_exsist == "m")
    {
        start = clock();
        while (1)
        {
            QString new_path = search_duplicates(p);
            QFile f(new_path);
            QTextStream out(&f);
            open_file(f, QIODeviceBase::WriteOnly, FILE_PERMS);
            modify_buffer();
            out << buffer;
            f.close();
            end = clock();
            if (((end - start) / CLOCKS_PER_SEC) > seconds)
            {
                qDebug() << "ERROR: Time expired\n";
                return;
            }
            return;
        }
    }
    if (f.exists(p) && actions_if_res_file_exsist == "r")
    {
        start = clock();
        while (1)
        {
            open_file(f, QIODeviceBase::WriteOnly);
            QTextStream out(&f);
            modify_buffer();
            out << buffer;
            f.close();
            end = clock();
            if (((end - start) / CLOCKS_PER_SEC) > seconds)
            {
                qDebug() << "ERROR: Time expired\n";
                return;
            }
            return;
        }
    }
    start = clock();
    while (1)
    {
        open_file(f, QIODeviceBase::WriteOnly, FILE_PERMS);
        modify_buffer();
        out << buffer;
        f.close();
        end = clock();
        if (((end - start) / CLOCKS_PER_SEC) > seconds)
        {
            qDebug() << "ERROR: Time expired\n";
            return;
        }
        break;
    }
}

void file_xor_mod::set_file_name(const QString& fname)
{
    file_name = fname;
    qDebug() << file_name;
}

void file_xor_mod::set_delete_input_files_flag(int flag)
{
    delete_input_files_flag = flag;
    qDebug() << delete_input_files_flag;
}

void file_xor_mod::set_path(const QString& ppath)
{
    path = ppath;
    qDebug() << path;
}

void file_xor_mod::set_action(const QString& act)
{
    actions_if_res_file_exsist = act;
    qDebug() << act;
}

void file_xor_mod::set_timer(int sec)
{
    seconds = sec;
    qDebug() << seconds;
}

void file_xor_mod::set_poll_timer(int p_sec)
{
    poll_seconds = p_sec;
    qDebug() << poll_seconds;
}

void file_xor_mod::set_variable(const QString& var)
{
    eight_byte_variable = var.toLongLong();
    //qDebug() << eight_byte_variable;
    qDebug() << var;
}

void file_xor_mod::rrun()
{
    bool res, p_flag = true;
    QFile input_file(file_name);
    open_file(input_file, QIODeviceBase::ReadWrite);
    read_from_file(&input_file, buffer, max_file_length);
    input_file.close();
    if (delete_input_files_flag)
        delete_file(input_file, file_name);
    if (seconds)
        store_resulting_file_timer(path);
    else
        store_resulting_file(path);
    qDebug() << "file_xor_mod::rrun()";
}
