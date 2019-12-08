# Malom-client
A kétszemélyes malom játékhoz a kliens oldal

<h1>Használata</h1>
A programot linux rendszer alatt tudod csak használni. Indításkor paraméterként vár egy portszámot, amivel a szerverre tudsz kapcsolódni.
A szerver megtalálható a repoban.

<h2>A játéktábla</h2>
Bal felső saroktól indulunk jobbra, majd pedig lefele. A számozás 0-tól kezdődik. Külső gyűrű[0-7], középső gyűrű[8-15], belső gyűrű[16-23].

<h2>Játékmenet</h2>
A játék indul, ha a két kliens csatlakozott. Ezután felváltva adtok meg egy-egy mezőt, ahova szeretnéd lerakni a korongot(0-23). 
Az INIT_STEPS után (alapért. 9) kezdődik a második rész. Itt két koordinátát kell megadni(honnan[0-23], hova[0-23]). Ha a játékosnak malma van,
akkor levehet egy korongot az ellenféltől(pozíció[0-23]). A játékot az nyeri, akinek több korongja marad.
