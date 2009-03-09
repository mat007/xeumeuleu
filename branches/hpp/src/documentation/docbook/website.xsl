<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:import href="website/chunk-tabular.xsl"/>
  <xsl:import href="highlighting/common.xsl"/>
  <xsl:import href="html/highlight.xsl"/>

  <xsl:param name="suppress.navigation" select="1"/>
  <xsl:param name="use.id.as.filename" select="1"/>
  <xsl:param name="navbgcolor">#FFFFFF</xsl:param>
  <xsl:param name="header.hr" select="0"/>
  <xsl:param name="footer.hr" select="0"/>
  <xsl:param name="text.home"/>
  <xsl:param name="nav.graphics" select="0"/>
  <xsl:param name="nav.pointer" select="0"/>
  <xsl:param name="nav.text.current.page">&#160;</xsl:param>
  <xsl:param name="nav.text.current.open">&#160;</xsl:param>
  <xsl:param name="highlight.source" select="1"/>
  <xsl:param name="generate.toc" select="'webpage/section toc'"/>

  <xsl:template name="gentext.nav.home"/>
  <xsl:template name="allpages.banner">
    <table width="100%" border="0">
      <tr>
        <td width="50%" align="left"><h1>XeuMeuLeu</h1></td>
        <td width="50%" align="right" valign="bottom">
          <a href="http://sourceforge.net/projects/xeumeuleu">
            <img src="http://sflogo.sourceforge.net/sflogo.php?group_id=165394&amp;type=12" border="0" alt="Get XeuMeuLeu at SourceForge.net. Fast, secure and Free Open Source software downloads"/>
          </a>
        </td>
      </tr>
    </table>
    <hr/>
    <table width="100%" border="0">
      <tr>
        <td width="100%" align="right" valign="top">
          <script type="text/javascript">document.write("Last Published: " + document.lastModified);</script>
        </td>
      </tr>
    </table>
    </xsl:template>

</xsl:stylesheet>
