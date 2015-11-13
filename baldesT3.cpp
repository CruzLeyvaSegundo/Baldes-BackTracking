#include<conio.h>
#include<string.h>
#include<stdio.h>
#include <cstdlib> 
#include<iostream.h>
#define LIM 30
struct Estado{
	int a; //VALOR ACTUAL DEL BALDE A
	int b; //VALOR ACTUAL DEL BALDE B
	int m; //MOVIMIENTO REALIZADO
};
int maxA,maxB;
int pivote;
int nSol=0;
int n=6;
Estado sol[LIM];
void impSol(int k)
{
    if(nSol>0)
    {   
        cout<<"Estado inicial(A,B) de los baldes=(0,0)"<<endl;          
    	for(int j=1; j<k; j++)
    	{
            if(sol[j].m==1)
            {
                cout<<"Op1(Llenar balde A)-> Estado actual(A,B)= ("<<sol[j].a<<","<<sol[j].b<<")";    
            }
            else if(sol[j].m==2)
            {
                cout<<"Op2(Llenar balde B)-> Estado actual(A,B)= ("<<sol[j].a<<","<<sol[j].b<<")";                  
            }       
            else if(sol[j].m==3)
            {
                cout<<"Op3(Vaciar balde A)-> Estado actual(A,B)= ("<<sol[j].a<<","<<sol[j].b<<")";                    
            }                  
            else if(sol[j].m==4)
            {
                cout<<"Op4(Vaciar balde A)-> Estado actual(A,B)= ("<<sol[j].a<<","<<sol[j].b<<")";                  
            }                  
            else if(sol[j].m==5)
            {
                cout<<"Op5(Pasar agua del BALDE A a el BALDE B sin derramar)->Estado actual(A,B)=("<<sol[j].a<<","<<sol[j].b<<")";                
            } 
            else if(sol[j].m==6)
            {
                cout<<"Op6(Pasar agua del BALDE B a el BALDE A sin derramar)->Estado actual(A,B)=("<<sol[j].a<<","<<sol[j].b<<")";                
            }        
            cout<<endl;                                   
    	}
    	cout<<endl;
    }
    else
    {
        cout<<"No existe una solucion posible al problema especificado";
    }
}
int construyeCandidatos(int k,Estado cand[])
{         
	int i, j, ncand=0;
	bool encontrado;
   	for(i=0; i<n; i++)
    {	
    	//cout<<"Construyendo candidatos ahora i="<<i<<endl;
		encontrado=false;
		for(int j=0;j<k;j++)//COMPARAMOS CON LAS SOLUCIONES DE LOS SUBPROBLEMAS DE LOS NIVELES ANTERIRORES
		{
            //SE VERIFICA QUE NO SE ENTRE EN UN BUCLE   
            //Verifica que no existan estados anteriores iguales al nuevo candidato que se hallara
		        if(i==0&&sol[j].a==maxA&&sol[j].b==sol[k-1].b)//VERIFICA OPERACION 1-- LLENAR BALDE A
		        {                                                                                                                                                                                                                                                                                                                       		
			        encontrado=true;
                } 
                else if(i==1&&sol[k-1].a==sol[j].a&&sol[j].b==maxB)//VERIFICA OPERACION 2-- LLENAR BALDE B     
                {
                    encontrado=true;
                }
                else if(i==2&&sol[j].a==0&&sol[j].b==sol[k-1].b)//VERIFICA OPERACION 3-- VACIAR BALDE A  
                {
                    encontrado=true;
                }
                else if(i==3&&sol[j].a==sol[k-1].a&&sol[j].b==0)//VERIFICA OPERACION 4-- VACIAR BALDE B     
                {
                    encontrado=true;
                }     
                else if(i==4)//VERIFICA OPERACION 5-- PASAR AGUA DEL BALDE A a el BALDE B SIN DERRAMAR    
                {
                    if(
                            (sol[k-1].a>=maxB-sol[k-1].b) 
                            &&(sol[j].a==sol[k-1].a-(maxB-sol[k-1].b))
                            &&(sol[j].b==maxB)
                       )
                    {
                        encontrado=true;                       
                    }
                    else if(
                            (sol[k-1].a<maxB-sol[k-1].b)
                            &&(sol[j].a==0)
                            &&(sol[j].b==sol[k-1].a+sol[k-1].b)
                            )
                    {
                        encontrado=true;
                    }
                }  
                else if(i==5)//VERIFICA OPERACION 6-- PASAR AGUA DEL BALDE B a el BALDE A SIN DERRAMAR       
                {
                    if(
                            (sol[k-1].b>=maxA-sol[k-1].a) 
                            &&(sol[j].a==maxA)
                            &&(sol[j].b==sol[k-1].b-(maxA-sol[k-1].a))
                       )
                    {
                        encontrado=true;                     
                    }
                    else if(
                            (sol[k-1].b<maxA-sol[k-1].a)
                            &&(sol[j].a==sol[k-1].a+sol[k-1].b)
                            &&(sol[j].b==0)
                            )
                    {
                        encontrado=true;
                    }
                }                
                if(encontrado)   
                {                     
                    /*                                     
                    //COMENTARIO DEBUG
                    cout<<"Incidencia en operacion["<<i+1<<"] con el estado("<<sol[j].a<<","<<sol[j].b<<") ubicado en el nivel: "<<k<<endl;
                    system("pause");  
                    */  
                    break; 
                }                 
        }
        //GENERA LOS CANDIDATOS NECESARIOS
		if(!encontrado)
		{            
            if(i==0)//GENERA EL CANDIDATO CON OPERACION 1-- LLENAR BALDE A
            {                                                                                                                                                                                                                                                                                                                       		
                cand[ncand].a=maxA;
                cand[ncand].b=sol[k-1].b;
                cand[ncand].m=1;	
            } 
            else if(i==1)//GENERA EL CANDIDATO CON OPERACION 2-- LLENAR BALDE B     
            {
                cand[ncand].a=sol[k-1].a;
                cand[ncand].b=maxB;
                cand[ncand].m=2;	
            }
            else if(i==2)//GENERA EL CANDIDATO CON OPERACION 3-- VACIAR BALDE A  
            {
                cand[ncand].a=0;
                cand[ncand].b=sol[k-1].b;
                cand[ncand].m=3;	
            }
            else if(i==3)//GENERA EL CANDIDATO CON OPERACION 4-- VACIAR BALDE B     
            {
                cand[ncand].a=sol[k-1].a;
                cand[ncand].b=0;
                cand[ncand].m=4;	
            }     
            else if(i==4)//GENERA EL CANDIDATO CON OPERACION 5-- PASAR AGUA DEL BALDE A a el BALDE B SIN DERRAMAR    
            {
                if(sol[k-1].a>=maxB-sol[k-1].b)//Cuando el volumen actual del BALDE A es mayor o igual que el de BALDE B 
                {
                cand[ncand].a=sol[k-1].a-(maxB-sol[k-1].b);
                cand[ncand].b=maxB;
                cand[ncand].m=5;	                    
                }
                else if(sol[k-1].a<maxB-sol[k-1].b)//Cuando el volumen actual del BALDE A es menor que el de BALDE B
                {
                cand[ncand].a=0;
                cand[ncand].b=sol[k-1].a+sol[k-1].b;
                cand[ncand].m=5;	
                }
            }  
            else if(i==5)//GENERA EL CANDIDATO CON OPERACION 6-- PASAR AGUA DEL BALDE B a el BALDE A SIN DERRAMAR       
            {
                if(sol[k-1].b>=maxA-sol[k-1].a)//Cuando el volumen actual del BALDE B es mayor o igual que el de BALDE A
                {
                cand[ncand].a=maxA;
                cand[ncand].b=sol[k-1].b-(maxA-sol[k-1].a);
                cand[ncand].m=6;	                     
                }
                else if(sol[k-1].b<maxA-sol[k-1].a)//Cuando el volumen actual del BALDE B es menor que el de BALDE A
                {
                cand[ncand].a=sol[k-1].a+sol[k-1].b;
                cand[ncand].b=0;
                cand[ncand].m=6;	
                }
            }
            /*
            //COMENTARIO DEBUG
            cout<<"Guardando candidato con operacion["<<i+1<<"] con el estado("<<cand[ncand].a<<","<<cand[ncand].b<<") ubicado en el nivel: "<<k<<endl;
            system("pause"); 
            */                                       
			ncand++;
        }
    }
    return ncand;
}
void bt(int k)
{   
	Estado cand[LIM];
	if(sol[k-1].a==pivote||sol[k-1].b==pivote) 
	{
        nSol++;
   		impSol(k);
    }
	else
	{      
		int ncand=construyeCandidatos(k, cand);
		for(int i=0; i<ncand; i++)
		{
                sol[k].a=cand[i].a;
                sol[k].b=cand[i].b;
                sol[k].m=cand[i].m;
                /*
                //COMENTARIO DEBUG
                cout<<"Posible solucion con operacion["<<sol[k].m<<"] con el estado("<<sol[k].a<<","<<sol[k].b<<") ubicado en el nivel: "<<k<<endl;
                system("pause");  
                */                   
			    bt(k+1);
      	}
   	}	
}
int main()
{
   	cout<<"Ingrese capacidad del balde A: ";  
   	cin>>maxA;
   	cout<<"Ingrese capacidad del balde B: ";  
   	cin>>maxB;   	
   	cout<<"Ingrese volumen de agua que busca obtener: ";  
   	cin>>pivote;
   	sol[0].a=0;
   	sol[0].a=0;
   	sol[0].a=0;
    bt(1);
    getch();
    return 0;
}


