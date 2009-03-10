<?xml version='1.0'?>
<!--
Copyright (c) 2008 Aryeh Leib Taurog

    This file is part of Lightweight Website

    Lightweight Website is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:exsl="http://exslt.org/common" version="1.0">
  <xsl:import href="xhtml/chunkfast.xsl"/>
  <xsl:import href="highlighting/common.xsl"/>
  <xsl:import href="html/highlight.xsl"/>

  <xsl:param name="suppress.navigation" select="1"/>
  <xsl:param name="use.id.as.filename" select="1"/>
  <xsl:param name="html.stylesheet" select="'style.css'"/>
  <xsl:param name="css.decoration" select="'0'"/>
  <xsl:param name="toc.max.depth" select="1"/>
  <xsl:param name="generate.toc" select="''"/>
  <xsl:param name="highlight.source" select="1"/>

  <xsl:template name="header.navigation">
    <div class="top-nav">
      <xsl:variable name="tocTree">
        <xsl:call-template name="make.toc">
          <xsl:with-param name="toc-context" select="/article"/>
          <xsl:with-param name="toc.title.p" select="false()"/>
          <xsl:with-param name="nodes" select="/article/section"/>
        </xsl:call-template>
      </xsl:variable>
      <xsl:apply-templates select="exsl:node-set($tocTree)" mode="filter.links">
        <xsl:with-param name="filter">
          <xsl:call-template name="href.target">
            <xsl:with-param name="object" select="ancestor-or-self::section[parent::article]"/>
            <xsl:with-param name="context" select="ancestor-or-self::section[parent::article]"/>
          </xsl:call-template>
        </xsl:with-param>
      </xsl:apply-templates>
    </div>
    <div class="sub-nav">
      <xsl:variable name="subTocTree">
        <xsl:call-template name="make.toc">
          <xsl:with-param name="toc.title.p" select="false()"/>
          <xsl:with-param name="toc-context" select="descendant-or-self::section[parent::section][1]"/>
          <xsl:with-param name="nodes" select="ancestor-or-self::section[parent::article]/section
                                             | ancestor-or-self::section[parent::article]/section/section
                                             | ancestor-or-self::section[parent::article]/section/section/section"/>
        </xsl:call-template>
      </xsl:variable>
      <xsl:apply-templates select="exsl:node-set($subTocTree)" mode="filter.links">
        <xsl:with-param name="filter">
            <xsl:call-template name="href.target">
              <xsl:with-param name="object" select="."/>
              <xsl:with-param name="context" select="."/>
            </xsl:call-template>
        </xsl:with-param>
      </xsl:apply-templates>
    </div>
  </xsl:template>

  <xsl:template match="@*|node()" mode="filter.links">
    <xsl:param name="filter" select="NO-FILTER"/>
    <xsl:choose>
      <xsl:when test="contains(@href,'index.html')"/>
      <xsl:when test="(string-length($filter) > 0 and contains(@href,$filter))">
      <span>
        <xsl:apply-templates select="@*|node()" mode="filter.links">
          <xsl:with-param name="filter" select="$filter"/>
        </xsl:apply-templates>
      </span>
    </xsl:when>
    <xsl:otherwise>
      <xsl:copy>
        <xsl:apply-templates select="@*|node()" mode="filter.links">
          <xsl:with-param name="filter" select="$filter"/>
        </xsl:apply-templates>
      </xsl:copy>
    </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template name="footer.navigation"/>

</xsl:stylesheet>
