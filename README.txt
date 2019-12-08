    functia getCookie:

	Va primi ca argument un char pointer;
	Functia va intoarce cookie-urile concatenate;
		-vom face o copie raspunsului si apoi vom cauta in aceasta 
"Set-Cookie";
		-vom face o copie stringului pe care il vom obtine;
		-vom extrage in cookie stringul obtinut marginit de " " si ";"
		-vom salva rezultatul in prajiturica
		-vom continua sa cautam in copy_parsare "Set-Cookie" si vom
aplica aceiasi pasi, doar ca vom concatena noul cookie la prajiturica deja 
obtinuta

    functia main:
	Vom declara intai mesajul trimis, raspunsul si socketul, iar apoi
structura json;

	TASK 1:
		-vom crea un socket respectand ip-ul, portul
		-vom trimite o cerere de tip get;

	TASK 2:
		-vom salva prajiturica necesara cu ajutorul functiei 
getCookie;
		-in json vom pastra structura de tip json (de la "{")
		-vom salva datele din json in t=structura noastra
		-vom salva in structura url_params dupa forma ceruta,
prin extragerea campurilor din structura json
		-ne vom conecta la server cu ajutorul parametrilor 
calculati anterior

	TASK 3 + TASK 4:
		-vom face la fel ca la task 2 si apoi ne vom conecta la
server si vom trimite cererea corespunzatoare

	TASK 5:
		-salvam prajiturica si campurile structurii json
		-observam ca avem 2 campuri numite url, asa ca pe primul
il vom salva intr un char pointer url1;
		-vom parsa url primit pentru a ne putea conecta la site
		-dupa ce calculam ip-ul si url_params ne vom conecta, vom
trimite o cerere;
		-raspunsul primit il vom parsa astfel incat sa trimitem 
inapoi doar structura de tip json;
		-ne vom conecta la server si vom trimite o cerere folosind
parametrii calculati anterior.
		
	
	
	

