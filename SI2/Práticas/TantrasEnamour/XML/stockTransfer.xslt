<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions"  xmlns:ns="http://TantrasEnamour/stockTransfer">
	<xsl:output method="text" version="1.0" encoding="UTF-8" indent="yes"/>

	<xsl:template name="LT_Ingrediente" match="/ns:stockTransfer/ns:transaction/ns:restaurantFrom/ns:ingredient">
			insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, QTY, VALIDITY, STOCK, RESTAURANT_ID)
			values
			(
				<xsl:value-of select="./@id"/>,
				<xsl:value-of select="../@id"/>,
				<xsl:value-of select="../../@id"/>,
				<xsl:value-of select="./@quantity"/>,
				&apos;<xsl:value-of select="./@vality"/>&apos;,
				<xsl:value-of select="./@quantity"/>,
				<xsl:value-of select="../@id"/>
			) ;
			insert into dbo.LOT(INGREDIENTS_ID, SUPPLIER_ID, INVOICE, QTY, VALIDITY, STOCK, RESTAURANT_ID)
			values
			(
				<xsl:value-of select="./@id"/>,
				<xsl:value-of select="../../ns:restaurantTo/@id"/>,
				<xsl:value-of select="../../@id"/>,
				-<xsl:value-of select="./@quantity"/>,
				&apos;<xsl:value-of select="./@vality"/>&apos;,
				-<xsl:value-of select="./@quantity"/>,
				<xsl:value-of select="../../ns:restaurantTo/@id"/>
			) ;			
		<xsl:apply-templates/>
	</xsl:template>
</xsl:stylesheet>
