https://www.hangge.com/blog/cache/detail_2506.html
@Bean 注解详解
1，使用说明
@Bean 注解作用在方法上
@Bean 指示一个方法返回一个 Spring 容器管理的 Bean
@Bean 方法名与返回类名一致，首字母小写
@Bean 一般和 @Component 或者 @Configuration 一起使用
@Bean 注解默认作用域为单例 singleton 作用域，可通过 @Scope(“prototype”) 设置为原型作用域
@Bean 默认是方法名 也可以指定名称

能产生Bean的注解有：

@Component
@Repository
@Controller
@Service
@Configration
@Bean

2.5 离职完毕
12K 
- 杭州公司：14 项目奖 15/16