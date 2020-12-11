#pragma once
class Vector {
public:
    double[] v; // значения вектора
    int n; // длина вектора
    Vector(int n) {
        this.n = n; 
        v = new double[n];
    }
	Vector(params double[] values) {
        n = values.Length;
        v = new double[n];
        for (int i = 0; i < n; i++) v[i] = values[i];
    }
    double this[int i] {
        get { return v[i]; }
        set { v[i] = value; }
    }
}