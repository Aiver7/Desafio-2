#ifndef MEDIDOR_H
#define MEDIDOR_H
#include <QTextStream>

struct Medidor {
    long iters{0};
    long bytes{0};
};

inline void med_add_iters(Medidor& m, long k){ m.iters += k; }

template<typename T>
inline void med_add_bytes(Medidor& m, const T&){ m.bytes += (long)sizeof(T); }

template<typename ArrT>
inline void med_add_bytes_arr(Medidor& m, const ArrT& arr){
    m.bytes += (long)(arr.n * sizeof(arr.items[0]));
}

inline void med_print(const char* tag, const Medidor& m){
    QTextStream out(stdout);
    out << "[medidor:" << tag << "] iters=" << m.iters << " bytes=" << m.bytes << "\n";
}
#endif
