use SI2_TP1;
/*
<competences xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="competences.xsd">
	<restaurant id="1" name="Name">
		<competence name="Nome da Competencia 1" compCount="23"/>
		<competence name="Nome da Competencia 2" compCount="1"/>
	</restaurant>
</competences>
*/
declare @COMPETENCES xml
set @COMPETENCES = (select * from competences_view FOR XML auto)
/*
if($a != $r/@restaurantid)
				then(
					element xpto {
						attribute id {$r/@restaurantid}
					}
				)
				else()
				let $a := $r/@restaurantid return (
					element xpto {
						attribute name {$r/@employeename}
					}
				)
*/
/*
<competences_view restaurantid="2" restaurantname="La Tartine" competenceid="1" employeename="Aaron CHEVALIER                                   " competencename="Chef                " />
<competences_view restaurantid="1" restaurantname="La Fondue" competenceid="1" employeename="César Henriques                                   " competencename="Chef                " />
<competences_view restaurantid="3" restaurantname="LA COCAGNE" competenceid="1" employeename="Aimon Chioccola                                   " competencename="Chef                " />
<competences_view restaurantid="4" restaurantname="Tête à Tête" competenceid="1" employeename="Esmeralda  Fantinati                              " competencename="Chef                " />
<competences_view restaurantid="2" restaurantname="La Tartine" competenceid="2" employeename="Acace AURILLAC                                    " competencename="Sous-Chef           " />
<competences_view restaurantid="1" restaurantname="La Fondue" competenceid="2" employeename="Diamantino Rodrigues                              " competencename="Sous-Chef           " />
<competences_view restaurantid="3" restaurantname="LA COCAGNE" competenceid="2" employeename="Alejandro Corgosinho                              " competencename="Sous-Chef           " />
<competences_view restaurantid="4" restaurantname="Tête à Tête" competenceid="2" employeename="Fidélis Galluzzi                                  " competencename="Sous-Chef           " />
<competences_view restaurantid="2" restaurantname="La Tartine" competenceid="3" employeename="Adele BUFFON                                      " competencename="Commis              " />
<competences_view restaurantid="1" restaurantname="La Fondue" competenceid="3" employeename="Deolinda Esteves                                  " competencename="Commis              " />
<competences_view restaurantid="3" restaurantname="LA COCAGNE" competenceid="3" employeename="Osírio  Curtarell                                 " competencename="Commis              " />
<competences_view restaurantid="4" restaurantname="Tête à Tête" competenceid="3" employeename="Guadalupe  Zottarelli                             " competencename="Commis              " />
 let $restaurantList := fn:distinct-values(/competences_view/@restaurantid) return (
 */

select @COMPETENCES.query('

	element competences
	{
		for $restaurants in distinct-values(/competences_view/@restaurantid)
		let $R_ID := $restaurants
		return (
		element restaurant 
		{
			attribute id {$R_ID},
			attribute name{distinct-values(/competences_view[@restaurantid=$R_ID]/@restaurantname)},
			for $compt in /competences_view where $compt/@restaurantid = $R_ID order by $compt/@competenceid return (
			element competence
			{
				attribute name {$compt/@competencename},
				attribute compCount {fn:count($compt/@competenceid)}
			}
			)
		}
		)
	}
') as result

/*
			for $r in /competences_view order by $r/@restaurantid  return 
			(
				element restaurant {
					attribute id {$r/@restaurantid},
					attribute name {$r/@restaurantname},
					element competence
					{
					for $c in /competences_view where $c/@restaurantid  = $r/@restaurantid  return 
					(
					element  competence 
					{
						attribute name {$r/@restaurantid},
						attribute compCount {$r/@restaurantid}
					}
					)
					}
				} 
			)

*/