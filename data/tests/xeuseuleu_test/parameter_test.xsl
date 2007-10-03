<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:param name="key1"/>
  <xsl:param name="key2"/>
  <xsl:template match="/root">
    <xsl:copy>
      <xsl:attribute name="key1">
        <xsl:value-of select="$key1"/>
      </xsl:attribute>
      <xsl:attribute name="key2">
        <xsl:value-of select="$key2"/>
      </xsl:attribute>
    </xsl:copy>
  </xsl:template>
</xsl:stylesheet>