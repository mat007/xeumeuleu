<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:variable name="cpd.summary" select="//duplication"/>
    <xsl:variable name="cpd.summary.count" select="sum($cpd.summary)"/>
    <xsl:variable name="cpd.summary.percent" select="round($cpd.summary/@passed * 10000 div $cpd.summary.count) div 100"/>

    <xsl:template match="/">
      <html>
        <head>
          <title>Copy/Paste Detector</title>
        </head>
      <body>
        <xsl:apply-templates/>
      </body>
      </html>
    </xsl:template>

    <xsl:template match="/pmd-cpd">

      <h1>Summary</h1>
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
  
      <h1>Duplications</h1>
      <xsl:for-each select="duplication">
        <xsl:variable name="lines" select="@lines"/>
        <h2>Duplication : <xsl:value-of select="$lines"/> lines - <xsl:value-of select="@tokens"/> tokens</h2>
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
          <pre class="code">
            <xsl:value-of select="codefragment"/>
          </pre>
        </xsl:for-each>

    </xsl:template>
    
    <xsl:template name="alternated-row">
      <xsl:attribute name="class">
        <xsl:if test="position() mod 2 = 1">a</xsl:if>
        <xsl:if test="position() mod 2 = 0">b</xsl:if>
      </xsl:attribute>
    </xsl:template>

</xsl:stylesheet>
