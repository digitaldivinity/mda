#ifndef KORCHAGIN_MULTIDIMENSIONAL_ARRAY
#define KORCHAGIN_MULTIDIMENSIONAL_ARRAY

template <class objType, int N>  class Mda{
	objType * arr;
	int * arrSize;
	short flags;
	public:
	Mda(int ars[N]){
		int dim=1;
		flags=1;
		arrSize=new int[N];
		for (int i=0;i<N;i++) dim*=ars[i];
		
		//запишем в arrSize сдвиги
		for (int i=0;i<N;i++) arrSize[i]=1;
		for (int i=0;i<N;i++)
			for (int j=i;j<N;j++)
				arrSize[i]*=ars[j];
				
		arr=new objType[dim];
	}
	Mda(int ars[N],objType * ptr):arr(ptr),arrSize(ars),flags(0){	}
	
	~Mda(){
		if (flags)
		{
			delete arr;
			delete arrSize;
		}
	}
	template <class TYPE> objType & operator()(TYPE n){
		return arr[n];
	}
	template <class HEAD, class ... TAIL> objType & operator() (HEAD n,TAIL ... args)
	{
		
		return Mda<objType,N-1>(&arrSize[1],arr+arrSize[1]*n)(args...);
	}
};
#endif
