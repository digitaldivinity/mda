#ifndef KORCHAGIN_MULTIDIMENSIONAL_ARRAY
#define KORCHAGIN_MULTIDIMENSIONAL_ARRAY

template <class objType, int N>  class Mda{
	objType * arr;
	int * arrSize;
	public:
	Mda(int ars[N]){
		int dim=1;
		arrSize=new int[N];
		for (int i=0;i<N;i++) dim*=ars[i];
		
		//запишем в arrSize сдвиги
		//например для 3,3,3
		//будет 27,9,3
		for (int i=0;i<N;i++)
			for (int j=i;j<N;j++)
				arrSize[i]*=ars[j];

		arr=new objType[dim];
	}
	private:
	template <class HEAD> int calculate(HEAD n){
		return n;
	}
	template <class HEAD,class ... TAIL> int calculate(HEAD n, TAIL ...args){
		++arrSize;
		int buf=(*(arrSize))*n+calculate(args...);
		--arrSize;
		return buf;
	}
	public:
	~Mda(){
		delete []arr;;
		delete []arrSize;
	}
	template <class TYPE> objType & operator()(TYPE n){
		return arr[calculate(n)];
	}
	template <class ... TAIL> objType & operator() (TAIL ... args)
	{
		return arr[calculate(args...)];
	}
};
#endif
