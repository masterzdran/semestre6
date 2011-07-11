use SI2_TP1;
declare @COMPETENCES xml
set @COMPETENCES = (select * from competences_view FOR XML auto)
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
			for $competences in distinct-values(/competences_view[@restaurantid=$R_ID]/@competenceid)
				let $C_ID := $competences
				return (
				element competence
				{
					attribute name {distinct-values(/competences_view[@restaurantid=$R_ID][@competenceid=$C_ID]/@competencename)},					
					attribute compCount {fn:count(/competences_view[@competenceid=$C_ID][@restaurantid = $R_ID] )}
				}
				
			)
		}
		)
	}
') as result;