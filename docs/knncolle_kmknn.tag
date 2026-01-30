<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
  <compound kind="file">
    <name>knncolle_kmknn.hpp</name>
    <path>/github/workspace/include/knncolle_kmknn/</path>
    <filename>knncolle__kmknn_8hpp.html</filename>
    <includes id="load__kmknn__prebuilt_8hpp" name="load_kmknn_prebuilt.hpp" local="yes" import="no" module="no" objc="no">load_kmknn_prebuilt.hpp</includes>
    <namespace>knncolle_kmknn</namespace>
  </compound>
  <compound kind="file">
    <name>load_kmknn_prebuilt.hpp</name>
    <path>/github/workspace/include/knncolle_kmknn/</path>
    <filename>load__kmknn__prebuilt_8hpp.html</filename>
    <class kind="struct">knncolle_kmknn::KmknnPrebuiltTypes</class>
    <namespace>knncolle_kmknn</namespace>
  </compound>
  <compound kind="class">
    <name>knncolle_kmknn::KmknnBuilder</name>
    <filename>classknncolle__kmknn_1_1KmknnBuilder.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>class Matrix_</templarg>
    <templarg>class DistanceMetricData_</templarg>
    <templarg>typename KmeansIndex_</templarg>
    <templarg>typename KmeansData_</templarg>
    <templarg>typename KmeansCluster_</templarg>
    <templarg>typename KmeansFloat_</templarg>
    <templarg>class KmeansMatrix_</templarg>
    <templarg>class DistanceMetricCenter_</templarg>
    <base>knncolle::Builder&lt; typename Index_, typename Data_, typename Distance_, class Matrix_ &gt;</base>
    <member kind="typedef">
      <type>KmknnOptions&lt; Index_, Data_, Distance_, KmeansIndex_, KmeansData_, KmeansCluster_, KmeansFloat_, KmeansMatrix_ &gt;</type>
      <name>Options</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a8956bd3195d022eb5b4c0b69e5dcc45f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KmknnBuilder</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a8d95fab3e38f2acd0c0ae33a651ac54c</anchor>
      <arglist>(std::shared_ptr&lt; const DistanceMetricData_ &gt; metric_data, std::shared_ptr&lt; const DistanceMetricCenter_ &gt; metric_center, Options options)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>KmknnBuilder</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a51fab6a43dba7fbde3a4c138b2695dbc</anchor>
      <arglist>(std::shared_ptr&lt; const DistanceMetricData_ &gt; metric_data, std::shared_ptr&lt; const DistanceMetricCenter_ &gt; metric_center)</arglist>
    </member>
    <member kind="function">
      <type>Options &amp;</type>
      <name>get_options</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>adb0ac04a27f8bf23e4d5dfcf3d2863b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_raw</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a69cbd818ec930b13314f6c3f00e4a247</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_unique</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>a59c9c836c77549822cd3c069f5e38714</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>build_known_shared</name>
      <anchorfile>classknncolle__kmknn_1_1KmknnBuilder.html</anchorfile>
      <anchor>ad2496dc0dea523d8b61052a41ecc59e8</anchor>
      <arglist>(const Matrix_ &amp;data) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>knncolle_kmknn::KmknnOptions</name>
    <filename>structknncolle__kmknn_1_1KmknnOptions.html</filename>
    <templarg>typename Index_</templarg>
    <templarg>typename Data_</templarg>
    <templarg>typename Distance_</templarg>
    <templarg>typename KmeansIndex_</templarg>
    <templarg>typename KmeansData_</templarg>
    <templarg>typename KmeansCluster_</templarg>
    <templarg>typename KmeansFloat_</templarg>
    <templarg>class KmeansMatrix_</templarg>
    <member kind="variable">
      <type>double</type>
      <name>power</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>abc25b2afd6e77663dd7e971c1a4649d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::shared_ptr&lt; kmeans::Initialize&lt; KmeansIndex_, KmeansData_, KmeansCluster_, KmeansFloat_, KmeansMatrix_ &gt; &gt;</type>
      <name>initialize_algorithm</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>a8703599b50b8f5e7c397bf514c2a2e52</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::shared_ptr&lt; kmeans::Refine&lt; KmeansIndex_, KmeansData_, KmeansCluster_, KmeansFloat_, KmeansMatrix_ &gt; &gt;</type>
      <name>refine_algorithm</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnOptions.html</anchorfile>
      <anchor>a91f70de83c9040c668fa67927f15a0bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>knncolle_kmknn::KmknnPrebuiltTypes</name>
    <filename>structknncolle__kmknn_1_1KmknnPrebuiltTypes.html</filename>
    <member kind="variable">
      <type>knncolle::NumericType</type>
      <name>kmeansfloat</name>
      <anchorfile>structknncolle__kmknn_1_1KmknnPrebuiltTypes.html</anchorfile>
      <anchor>a6c7162a3f4b401f1ebe6da39940caf54</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>knncolle_kmknn</name>
    <filename>namespaceknncolle__kmknn.html</filename>
    <class kind="class">knncolle_kmknn::KmknnBuilder</class>
    <class kind="struct">knncolle_kmknn::KmknnOptions</class>
    <class kind="struct">knncolle_kmknn::KmknnPrebuiltTypes</class>
    <member kind="function">
      <type>std::function&lt; void(const std::filesystem::path &amp;)&gt; &amp;</type>
      <name>custom_save_for_kmknn_kmeansfloat</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a4a433e904efb23db4f47567530f301e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>KmknnPrebuiltTypes</type>
      <name>load_kmknn_prebuilt_types</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>a2e91a868a2c55f67bb0bf52f82f3966b</anchor>
      <arglist>(const std::filesystem::path &amp;dir)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>load_kmknn_prebuilt</name>
      <anchorfile>namespaceknncolle__kmknn.html</anchorfile>
      <anchor>abc6e3b15e3fa1d71b0d99c4a963d9863</anchor>
      <arglist>(const std::filesystem::path &amp;dir)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>knncolle bindings for KMKNN</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
