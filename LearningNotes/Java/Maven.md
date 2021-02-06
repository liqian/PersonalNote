# IDEA Create Maven Project
- Create from archetype:
1. archetype的作用是什么呢,archetype英文意思为典型,在此处应该翻译为项目模型或者说是项目的骨架,  
帮你生成某一种项目的通用文件布局,此处我们选择初学者常用的maven-archetype-webapp
2. 如果创建出来的工程是空的，是因为安装的IntelliJ IDEA默认使用的都是国外的Maven地址,  
模板根本没下载下来,所以创建出来就啥都没,如果你把镜像设置好了,按以上步骤操作,就能正常生成出简单的webapp项目结构了.


# Maven Plugin
## maven-project-info-reports-plugin
- 查看maven依赖的详细信息
- 添加plugin
```maven
<build>
    <pluginManagement><!-- lock down plugins versions to avoid using Maven defaults (may be moved to parent pom) -->
      <plugins>
      <plugin>
          <groupId>org.apache.maven.plugins</groupId>
          <artifactId>maven-project-info-reports-plugin</artifactId>
          <version>3.0.0</version>
          <!--> version 可以去maven的中央仓库找最新的 <-->
      </plugins>
    </pluginManagement>
  </build>
```
- 添加report：
```maven
<reporting>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-project-info-reports-plugin</artifactId>
        <reportSets>
          <reportSet>
            <reports>
              <report>dependencies</report>
              <report>licenses</report>
            </reports>
          </reportSet>
        </reportSets>
      </plugin>
    </plugins>
</reporting>
```
- 使用： mvn project-info-reports:dependencies  
在target下生成一个site文件夹，里边有个dependency.html，进去就能看到详细的依赖的信息
