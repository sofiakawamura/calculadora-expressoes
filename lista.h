#ifndef LISTA
#define LISTA
class Lista
{
protected:
    typedef struct sNo
    {
        void* Info;
        struct sNo *Prox;

    } sNo;
    typedef sNo *pNo;
    static char Erro;
    char Valida;
    pNo Inicio;
    void DescarteTudo();

public:
    static char DeuErro();
    char eValida() const;
    Lista();
    Lista(const Lista &);
    ~Lista();
    Lista &operator=(const Lista &);
    void Incorpore(void*);
    virtual int Contem(void*) const;
    virtual void Descarte(void*);
    virtual char *NaFormaDeString() const;
    void IncorporeNoInicio(void*);
    void* DescarteDoInicio();
    void IncorporeNoFinal(void*);
    void* DescarteDoFinal();
};
#endif
