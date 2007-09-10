<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/root">
    <new-root>
      <xsl:apply-templates select="element"/>
    </new-root>
  </xsl:template>
  <xsl:template match="element">
    <transformed/>
  </xsl:template>
</xsl:stylesheet>
