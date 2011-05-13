<?xml version="1.0" ?>
<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:xlf="urn:oasis:names:tc:xliff:document:1.1"
 xmlns:str="http://exslt.org/strings">
 <xsl:output method="html" encoding="utf-8"/>
 <xsl:template match="/">
 <html>
		<head>
			<title></title>
			<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
			<link href="http://europass.cedefop.europa.eu/instruments/css/html.css" type="text/css" rel="stylesheet"/>
		</head>
		<body>
			<table width="710" border="0" cellspacing="0" cellpadding="0" class="Grid">
				<tbody>
					<tr class="title">
						<td></td>
						<th colspan="2"><xsl:value-of select="//xlf:trans-unit[@id='/step5/understanding']/xlf:target"/></th>
						<th colspan="2"><xsl:value-of select="//xlf:trans-unit[@id='/step5/speaking']/xlf:target"/></th>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/writing']/xlf:target"/></th>
					</tr>
					<tr class="subheader">
						<td></td>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/listening']/xlf:target"/></th>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/reading']/xlf:target"/></th>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/spokeninteraction']/xlf:target"/></th>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/spokenproduction']/xlf:target"/></th>
						<th><xsl:value-of select="//xlf:trans-unit[@id='/step5/writing']/xlf:target"/></th>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/a1']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='a1']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/a1_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/a2']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='a2']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/a2_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/b1']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='b1']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/b1_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/b2']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='b2']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/b2_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/c1']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='c1']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/c1_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
					<tr class="level">
						<th><xsl:value-of select="//xlf:trans-unit[@id='/c2']/xlf:target"/></th>
						<xsl:for-each select="//xlf:group[@resname='c2']">
							<td><xsl:value-of select="./xlf:trans-unit[@id='/c2_ex.desc']/xlf:target"/></td>
						</xsl:for-each>
					</tr>
				</tbody>
			</table>
		</body>
	</html>
	</xsl:template>
	</xsl:stylesheet>


