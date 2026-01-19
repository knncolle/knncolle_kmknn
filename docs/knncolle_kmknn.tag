<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
  <compound kind="file">
    <name>knncolle_kmknn.hpp</name>
    <path>/github/workspace/include/knncolle_kmknn/</path>
    <filename>knncolle__kmknn_8hpp.html</filename>
    <class kind="struct">knncolle_kmknn::KmknnOptions</class>
    <class kind="class">knncolle_kmknn::KmknnBuilder</class>
    <namespace>knncolle_kmknn</namespace>
  </compound>
  <compound kind="class">
    <name>knncolle_kmknn::KmknnBuilder</name>
    <filename>classknncolle__kmknn_1_1KmknnBuilder.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class Matrix_</templarg>
    <templarg>class DistanceMetric_</templarg>
    <templarg>class KmeansMatrix_</templarg>
    <base>knncolle::Builder&lt; typename Index_, typename Data_, typename Distance_, class Matrix_ &gt;</base>
    <member kind="typedef">
      <type>KmknnOptions&lt; Index_, Data_, Distance_, KmeansMatrix_ &gt;</type>
      <name>Options</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a11b086d90c33777274fa48c0657238e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KmknnBuilder</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>ac841e15738c745bd12672a62f77f6041</anchor>
      <arglist>(std::shared_ptr&lt; const DistanceMetric_ &gt; metric, Options options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KmknnBuilder</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a4e371713bc2d5499550516f7625dcdc4</anchor>
      <arglist>(std::shared_ptr&lt; const DistanceMetric_ &gt; metric)</arglist>
    </member>
    <member kind="function">
      <type>Options &amp;</type>
      <name>get_options</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a7cc86e827674d374a9090c6f4e9300ea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_raw</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a31992acfce7ac76c9181ccb1b416fc07</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_unique</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>abb53f6576840a869640b0e1b797e9193</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_shared</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a249418610a4c936e586334538c7b900f</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>knncolle_kmknn::KmknnOptions</name>
    <filename>structknncolle__kmknn_1_1KmknnOptions.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class KmeansMatrix_</templarg>
    <member kind="variable">
      <type>double</type>
      <name>power</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>a84b020741aac4160fed42a291d054216</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::shared_ptr&lt; Initialize&lt; Index_, Data_, Distance_, KmeansMatrix_ &gt; &gt;</type>
      <name>initialize_algorithm</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>a72b15c4565052f08de373f00f90c46ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::shared_ptr&lt; Refine&lt; Index_, Data_, Distance_, KmeansMatrix_ &gt; &gt;</type>
      <name>refine_algorithm</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>a3e70f115b4eb557512fa7199c681f853</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>knncolle_kmknn</name>
    <filename>namespaceknncolle__kmknn.html</filename>
    <class kind="class">knncolle_kmknn::KmknnBuilder</class>
    <class kind="struct">knncolle_kmknn::KmknnOptions</class>
    <member kind="typedef">
      <type>decltype(std::declval&lt; Data_ &gt;() - std::declval&lt; Distance_ &gt;())</type>
      <name>Common</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>ab89a88b7e80686823b2d6e869b46d33c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>knncolle::DistanceMetric&lt; Common&lt; Data_, Distance_ &gt;, Distance_ &gt;</type>
      <name>DistanceMetric</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a951ca343a2296f4aeffa1e2bb84c6bec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>knncolle::EuclideanDistance&lt; Common&lt; Data_, Distance_ &gt;, Distance_ &gt;</type>
      <name>EuclideanDistance</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a14989deec2423f5045ccd5366b24ca3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>knncolle::ManhattanDistance&lt; Common&lt; Data_, Distance_ &gt;, Distance_ &gt;</type>
      <name>ManhattanDistance</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a11476f42c27e84a8053827c3386714f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::Initialize&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>Initialize</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>af1529d337336e9be814dbb82aaac452b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::InitializeRandom&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>InitializeRandom</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a4ea87c7589eb69e6fde509581584c786</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::InitializeKmeanspp&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>InitializeKmeanspp</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a3cd0b450d82b722d17fe6f2890b895ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::InitializeNone&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>InitializeNone</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a0fd74adc73ae84b227d91bda23b8411c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::InitializeVariancePartition&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>InitializeVariancePartition</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a63fefb2020a20ccdaa88e1cb64a82ad4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::Refine&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>Refine</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>aa406fc698a8543c13d2081467099000e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::RefineLloyd&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>RefineLloyd</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>ad19250ce8179359cd6118cdf2e9b3936</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>kmeans::RefineHartiganWong&lt; Index_, Common&lt; Data_, Distance_ &gt;, Index_, Common&lt; Data_, Distance_ &gt;, KmeansMatrix_ &gt;</type>
      <name>RefineHartiganWong</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a82947272781cd9cc6040f859cf99a3f7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>knncolle bindings for KMKNN</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
