//kompakt
typedef unsigned int ui;
template <typename T, size_t N, size_t M>
struct Matrix {
	vector<T> t[N];
	Matrix() {
		for(ui i=0;i<N;++i) t[i].resize(M);
	}
	
	const vector<T>& operator[](size_t x) const {
		return t[x];
	}
	
	Matrix(initializer_list<T> lst) {
		int ind=0;
		for(ui i=0;i<N;++i) {
			t[i].resize(M);
			for(ui j=0;j<M;++j) {
				t[i][j]=*(lst.begin()+ind++);
			}
		}
	}
	
	Matrix<T,N,M> operator+(const Matrix<T,N,M>& masik) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]+masik.t[i][j]; return res;}
	Matrix<T,N,M> operator-(const Matrix<T,N,M>& masik) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]-masik.t[i][j]; return res;}

	Matrix<T,N,M> operator%(T v) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]%v; return res;}
	Matrix<T,N,M> operator+(T v) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]+v; return res;}
	Matrix<T,N,M> operator-(T v) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]-v; return res;}
	Matrix<T,N,M> operator*(T v) { Matrix<T,N,M> res; for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) res.t[i][j]=t[i][j]*v; return res;}

	Matrix<T,N,M>& operator%=(T v) { for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) t[i][j]=t[i][j]%v; return *this;}
	Matrix<T,N,M>& operator+=(T v) { for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) t[i][j]=t[i][j]+v; return *this;}
	Matrix<T,N,M>& operator-=(T v) { for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) t[i][j]=t[i][j]-v; return *this;}
	Matrix<T,N,M>& operator*=(T v) { for(ui i=0;i<N;++i) for(ui j=0;j<M;++j) t[i][j]=t[i][j]*v; return *this;}
	
	template<size_t P>
	Matrix<T,N,P> operator*(const Matrix<T,M,P>& masik) {
		Matrix<T,N,P> res;
		for(ui i=0;i<N;++i) {
			for(ui j=0;j<P;++j) {
				T curr=0;
				for(ui k=0;k<M;++k) {
					curr+=t[i][k]*masik.t[k][j];
				}
				
				res.t[i][j]=curr;
			}
		}
		
		return res;
	}
};


//dinamikus matrix

template<typename T> 
T fastpow(T x, int a, T mod) {
	if(a==0) return 1;
	if(a==1) return x;
	
	T fele=fastpow(x, a/2, mod);
	T ans=(fele*fele)%mod;
	
	if(a&1) ans=(ans*x)%mod;
	
	return ans;
}

template<typename T>
struct Matrix {
	unsigned int N, M;
	vector<vector<T>> t;
	
	Matrix(unsigned int N, unsigned int M) {
		this->N=N;
		this->M=M;
		t=vector<vector<T>>(N);
		for(unsigned int i=0;i<N;++i) {
			t[i]=vector<T>(M, 0);
		}
	}
	
	void swap(unsigned int i, unsigned int j) {
		t[i].swap(t[j]);
	}
	
	Matrix<T> transpose() {
		Matrix<T> res;
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				res.t[j][i]=t[i][j];
			}
		}
		
		return res;
	}
	
	void operator += (const Matrix<T>& masik) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]+=masik.t[i][j];
			}
		}
	}
	
	Matrix<T> operator+(const Matrix<T>& masik) {
		Matrix<T> res=*this;
		res += masik;
		
		return res;
	}
	
	Matrix<T> operator*(const Matrix<T>& masik) {
		assert(M==masik.N);
		unsigned int P=masik.M;
		Matrix<T> res(N, P);
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<P;++j) {
				T akt=0;
				for(unsigned int k=0;k<M;++k) {
					akt+=t[i][k]*masik.t[k][j];
				}
				
				res.t[i][j]=akt;
			}
		}
		
		return res;
	}
	
	void operator*= (const Matrix<T>& masik) {
		this = this * masik;
	}
	
	void operator*=(T scalar) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]*=scalar;
			}
		}
	}
	
	Matrix<T> operator*(T scalar) {
		Matrix<T> res=*this;
		res *= scalar;
		
		return res;
	}
	
	void operator %= (T scalar) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]%=scalar;
			}
		}
	}
	
	Matrix<T> operator %(T scalar) {
		Matrix<T> res=*this;
		res %= scalar;
		
		return res;
	}
	
	template<typename Tt>
	friend ostream& operator<<(ostream& os, const Matrix<Tt>& m);  
	
	template<typename Tt>
	friend istream& operator>>(istream& is, const Matrix<Tt>& m);  
};

template<typename T>
ostream& operator<<(ostream& os, const Matrix<T>& m) {
	for(unsigned int i=0;i<m.N;++i) {
		for(unsigned int j=0;j<m.M;++j) {
			cout<<m.t[i][j]<<" ";
		}cout<<"\n";
	}
	
	return os;
}

template<typename T>
istream& operator>>(istream& is, Matrix<T>& m) {
	for(unsigned int i=0;i<m.N;++i) {
		for(unsigned int j=0;j<m.M;++j) {
			is>>m.t[i][j];
		}
	}
	
	return is;
}

template<typename T> 
int gauss(Matrix<T> m, vector<T>& b,  vector<T>& sol, T mod) {
	unsigned int N=m.N, M=m.M;
	vector<int> where(M, -1);

	for(unsigned int i=0, j=0;i<N && j<M;i++) {
		int mxind=i;
		for(unsigned int k=i;k<N;++k) {
			if(abs(m.t[mxind][j])<abs(m.t[k][j])) {
				mxind=k;
			}
		}
		
		if(m.t[mxind][j]==0) continue ;
		
		m.swap(mxind, i);
		swap(b[mxind], b[i]);
		
		where[i]=j;
		
		for(unsigned int k=0;k<N;++k){
			if(k!=i) {
				if(m.t[k][j]==0) continue ;
				T c=m.t[k][j]*fastpow(m.t[i][j], mod-2, mod);
				for(unsigned int l=0;l<M;++l) {
					m.t[k][l]=((m.t[k][l]-c*m.t[i][l])%mod+mod)%mod;
				}
				b[k]=((b[k]-c*b[i])%mod+mod)%mod;
			}
		}
		
		j++;
	}
	

	
	
	sol.assign(M, 0);
	for(unsigned int i=0;i<M;++i) {
		if(where[i]!=-1) {
			sol[i]=((b[where[i]]*fastpow(m.t[where[i]][i], mod-2, mod))%mod+mod)%mod;
		}
	}

	
	for(unsigned int i=0;i<N;++i) {
		T sum=0;
		
		for(unsigned int j=0;j<M;++j) {
			sum+=m.t[i][j]*sol[j];
			sum%=mod;
		}
		
		if((sum-b[i])%mod!=0) { 
			return 0;
		}
	}
	
	for(unsigned int i=0;i<M;++i) {
		if(where[i]==-1) {
			return 2;
		}
	}
	
	return 1;
}










//INKÁBB Matrix Hatv-ra
template<typename T, unsigned int N, unsigned int M>
struct Matrix {
	vector<T> t[N];
	
	Matrix() {
		for(unsigned int i=0;i<N;++i) {
			t[i]=vector<T>(M, 0);
		}
	}
	
	Matrix(initializer_list<T> lst) {
		unsigned int ind=0;
		for(unsigned int i=0;i<N;++i) {
			t[i]=vector<T>(M, 0);
			
			for(unsigned int j=0;j<M;++j) {
				t[i][j]=*(lst.begin()+ind++);
			}	
		}
	}
	
	void swap(unsigned int i, unsigned int j) {
		t[i].swap(t[j]);
	}
	
	Matrix<T, M, N> transpose() {
		Matrix<T, M, N> res;
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				res.t[j][i]=t[i][j];
			}
		}
		
		return res;
	}
	
	void operator += (const Matrix<T, N, M>& masik) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]+=masik.t[i][j];
			}
		}
	}
	
	Matrix<T, N, M> operator+(const Matrix<T, N, M>& masik) {
		Matrix<T, N, M> res=*this;
		res += masik;
		
		return res;
	}
	
	template<unsigned int P>
	Matrix<T, N, P> operator*(const Matrix<T, M, P>& masik) {
		Matrix<T, N, P> res;
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<P;++j) {
				T akt=0;
				for(unsigned int k=0;k<M;++k) {
					akt+=t[i][k]*masik.t[k][j];
				}
				
				res.t[i][j]=akt;
			}
		}
		
		return res;
	}
	
	template<unsigned int P>
	void operator*= (const Matrix<T, M, P>& masik) {
		this = this * masik;
	}
	
	void operator*=(T scalar) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]*=scalar;
			}
		}
	}
	
	Matrix<T, N, M> operator*(T scalar) {
		Matrix<T, N, M> res=*this;
		res *= scalar;
		
		return res;
	}
	
	void operator %= (T scalar) {
		for(unsigned int i=0;i<N;++i) {
			for(unsigned int j=0;j<M;++j) {
				t[i][j]%=scalar;
			}
		}
	}
	
	Matrix<T, N, M> operator %(T scalar) {
		Matrix<T, N, M> res=*this;
		res %= scalar;
		
		return res;
	}
	

	template<typename Tt, unsigned int Nn, unsigned int Mm>
	friend ostream& operator<<(ostream& os, const Matrix<Tt, Nn, Mm>& m);  
	
	template<typename Tt, unsigned int Nn, unsigned int Mm>
	friend istream& operator>>(istream& is, const Matrix<Tt, Nn, Mm>& m);  
};

template<typename T, unsigned int N, unsigned int M>
ostream& operator<<(ostream& os, const Matrix<T, N, M>& m) {
	for(unsigned int i=0;i<N;++i) {
		for(unsigned int j=0;j<M;++j) {
			cout<<m.t[i][j]<<" ";
		}cout<<"\n";
	}
	
	return os;
}

template<typename T, unsigned int N, unsigned int M>
istream& operator>>(istream& is, Matrix<T, N, M>& m) {
	for(unsigned int i=0;i<N;++i) {
		for(unsigned int j=0;j<M;++j) {
			is>>m.t[i][j];
		}
	}
	
	return is;
}

