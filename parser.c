
char * token = gettoken();
void prog(){
    if(token == "begin"){
        gettoken();
        st_list();
    }
    else
        eror("отсылаем тип хибы интом или чем-нибудь");
}
void st_list(){
    switch (atoi(token))
    {
    case (RETURN):
        gettoken();
        break;
    
    case (VAR):
        gettoken();
        break;
    case (ID):
        gettoken();
        state
        break;
    case ():
        gettoken();
        break;
    case (ELSE):
        gettoken();
        break;
    case (ELSE):
        gettoken();
        break;
    case (ELSE):
        gettoken();
        break;
    }
    else{}

}