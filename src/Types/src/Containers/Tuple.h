#pragma once

template <typename T1, typename T2>
struct Tuple {
    
    Tuple() {

    }

    Tuple (T1 t1, T2 t2) {
        this->t1 = t1;
        this->t2 = t2;
    }

    template <typename T1cnv, typename T2cnv>
    Tuple(T1cnv t1, T2cnv t2) {
      this->t1 = (T1)t1;
      this->t2 = (T2)t2;
    }

    T1 t1;
    T2 t2;
};