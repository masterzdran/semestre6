<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions"  xmlns:ns="http://TantrasEnamour/stockTransfer">
	<xsl:output method="text" version="1.0" encoding="UTF-8" indent="yes"/>

	<xsl:template name="LT_Ingrediente" match="/ns:stockTransfer/ns:transaction/ns:restaurantFrom/ns:ingredient">
			insert into TABLE ( id, name, quantity, unit)
			values
			(
				<xsl:value-of select="./@id"/>,
				&apos;<xsl:value-of select="./@name"/>&apos;,
				<xsl:value-of select="./@quantity"/>,
				&apos;<xsl:value-of select="./@unit"/>&apos;
			) ;
			<xsl:apply-templates/>
	</xsl:template>
	<xsl:template name="LT_Restaurantes" match="/ns:stockTransfer/ns:transaction">
			----->Nome do Restaurante de Origem: 
				<xsl:value-of select="./ns:restaurantFrom/@id"/> <xsl:value-of select="./ns:restaurantFrom/@name"/> 
			----->Nome do Restaurante de Destino: 
				<xsl:value-of select="./ns:restaurantTo/@id"/> <xsl:value-of select="./ns:restaurantFrom/@name"/> 
				<xsl:apply-templates/>
	</xsl:template>

</xsl:stylesheet>
