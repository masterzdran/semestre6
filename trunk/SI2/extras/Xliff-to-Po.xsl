<?xml version="1.0" ?>
<xsl:stylesheet version="2.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:xlf="urn:oasis:names:tc:xliff:document:1.1"
 xmlns:xsd="http://www.w3.org/2001/XMLSchema"
 xmlns:fn="http://www.w3.org/2005/xpath-functions"
 xmlns:xalan="http://xml.apache.org/xalan"
>
 <xsl:output method="text" encoding="utf-8" xalan:content-handler="org.apache.xml.serializer.ToTextStream"/>
 <xsl:template match="/">
 <xsl:for-each select="//xsd:documentation">
	<xsl:value-of select="fn:replace(., 'xl[if]*f', 'po')"/>
</xsl:for-each>
  <xsl:text>#
msgid ""
msgstr ""
"MIME-Version: 1.0\n"
"Content-Type: text/plain; charset=UTF-8\n"
"Content-Transfer-Encoding: 8bit\n"
</xsl:text>
  <xsl:for-each select="//xlf:trans-unit">
   <xsl:text>
msgid "</xsl:text><xsl:value-of select="normalize-space(xlf:source)"/><xsl:text>"
msgstr "</xsl:text><xsl:value-of select="normalize-space(xlf:target)"/><xsl:text>"
</xsl:text>
  </xsl:for-each>
 </xsl:template>
</xsl:stylesheet>