<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:variable name="tests.summary" select="//SubTestCases"/>
    <xsl:variable name="tests.summary.count" select="$tests.summary/@passed + $tests.summary/@failed"/>
    <xsl:variable name="tests.summary.percent" select="round($tests.summary/@passed * 10000 div $tests.summary.count) div 100"/>

    <xsl:template match="/">
      <section id="tests">
        <title>Unit Tests</title>
        <xsl:apply-templates/>
      </section>
    </xsl:template>

    <xsl:template match="/TestResult">

      <section>
        <title>Summary</title>
        <table class="bodyTable">
        <thead>
          <tr class="a">
            <th>Tests</th>
            <th>Failures</th>
            <th>Success rate</th>
          </tr>
        </thead>
        <xsl:variable name="tests.passed" select="sum(TestSuite/@test_cases_passed)"/>
        <xsl:variable name="tests.failed" select="sum(TestSuite/@test_cases_failed)"/>
        <xsl:variable name="tests.count" select="$tests.passed + $tests.failed"/>
        <xsl:variable name="tests.percent" select="round($tests.passed * 10000 div $tests.count) div 100"/>
          <tr class="b">
            <td><xsl:value-of select="$tests.count"/></td>
            <td><xsl:value-of select="$tests.failed"/></td>
            <td><xsl:value-of select="$tests.percent"/>%</td>
          </tr>
        </table>
      </section>

      <section>
        <title>Test Suites</title>
        <table class="bodyTable">
        <thead>
          <tr class="a">
            <th>Suite</th>
            <th>Tests</th>
            <th>Failures</th>
            <th>Success rate</th>
          </tr>
        </thead>
        <xsl:for-each select="TestSuite">
          <tr>
            <xsl:call-template name="alternated-row"/>
            <td><xsl:value-of select="@name"/></td>
            <xsl:variable name="tests.count" select="@test_cases_passed + @test_cases_failed"/>
            <xsl:variable name="tests.percent" select="round(@test_cases_passed * 10000 div $tests.count) div 100"/>
            <td><xsl:value-of select="$tests.count"/></td>
            <td><xsl:value-of select="@test_cases_failed"/></td>
            <td><xsl:value-of select="$tests.percent"/>%</td>
          </tr>
        </xsl:for-each>
        </table>
      </section>

      <section>
        <title>Test Cases</title>
        <xsl:for-each select="TestSuite">
          <section>
            <title><xsl:value-of select="@name"/></title>
            <table class="bodyTable">
            <thead>
              <tr class="a">
                <th>Status</th>
                <th>Test</th>
              </tr>
            </thead>
            <xsl:for-each select="TestCase">
            <tr>
              <xsl:call-template name="alternated-row"/>
              <xsl:variable name="status" select="@result"/>
              <td>
                <xsl:if test="$status='failed'">
                  <xsl:attribute name="bgcolor">#FF3333</xsl:attribute>
                </xsl:if>
                <xsl:if test="$status='passed'">
                  <xsl:attribute name="bgcolor">#33FF66</xsl:attribute>
                </xsl:if>
                <xsl:value-of select="@result"/>
              </td>
              <td><xsl:value-of select="@name"/></td>
            </tr>
            </xsl:for-each>
            </table>
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
