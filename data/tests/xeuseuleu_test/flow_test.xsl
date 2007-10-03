<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/root">
    <flow-root>
      <xsl:apply-templates select="new-root"/>
    </flow-root>
  </xsl:template>
  <xsl:template match="new-root">
    <element/>
  </xsl:template>
</xsl:stylesheet>
