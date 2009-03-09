<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:variable name="cpd.summary" select="//duplication"/>
  <xsl:variable name="cpd.summary.count" select="sum($cpd.summary)"/>
  <xsl:variable name="cpd.summary.percent" select="round($cpd.summary/@passed * 10000 div $cpd.summary.count) div 100"/>

  <xsl:template match="/">
    <webpage id="cpd">
      <head>
        <title>Copy/Paste Detector</title>
      </head>
      <xsl:apply-templates/>
    </webpage>
  </xsl:template>

  <xsl:template match="/pmd-cpd">

    <section>
      <title>Summary</title>
      <table class="bodyTable">
        <tr class="a">
          <th>Total number of duplications</th>
          <td><xsl:value-of select="count(duplication)"/></td>
        </tr>
        <tr class="b">
          <th>Total number of duplicate lines</th>
          <td><xsl:value-of select="sum(duplication/@lines)"/></td>
        </tr>
        <tr class="a">
          <th>Total number of duplicate tokens</th>
          <td><xsl:value-of select="sum(duplication/@tokens)"/></td>
        </tr>
        <tr class="b">
          <th>Total number of files with duplicates</th>
          <td><xsl:value-of select="count(duplication/file)"/></td>
        </tr>
      </table>
    </section>

    <section>
      <title>Duplications</title>
      <xsl:for-each select="duplication">
        <xsl:variable name="lines" select="@lines"/>
        <section>
          <title>Duplication : <xsl:value-of select="$lines"/> lines - <xsl:value-of select="@tokens"/> tokens</title>
          <table class="bodyTable">
            <tr class="a">
              <thead>
                <th>File</th>
                <th>Location</th>
              </thead>
            </tr>
            <xsl:for-each select="file">
              <tr>
                <xsl:call-template name="alternated-row"/>
                <td><xsl:value-of select="@path"/></td>
                <td><xsl:value-of select="@line"/> - <xsl:value-of select="@line + $lines - 1"/></td>
              </tr>
              </xsl:for-each>
            </table>
            <programlisting langage="cpp">
              <xsl:value-of select="codefragment"/>
            </programlisting>
          </section>
        </xsl:for-each>
      </section>

  </xsl:template>

  <xsl:template name="alternated-row">
    <xsl:attribute name="class">
      <xsl:if test="position() mod 2 = 1">a</xsl:if>
      <xsl:if test="position() mod 2 = 0">b</xsl:if>
    </xsl:attribute>
  </xsl:template>

</xsl:stylesheet>
