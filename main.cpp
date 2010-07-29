#include <QtCore>
#include "wordpressapi.h"
#include "wordpresspost.h"
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QString url, user, pass, title, description, category, status,tags;
    url = "http://aecsmaa.wordpress.com";
    user = "kshlmster";
    pass = "Face1048";
    wordpressApi *service = new wordpressApi(url, &app);
    service->setUsername(user);
    service->setPassword(pass);
    service->getBlogid();

    wordpressPost post;
    title = "Test 3" ;
    post.setTitle(title);
    description = "<p>Test <em>test</em> test <span style=\"color: #00ff00;\">test</span></p><p style=\"text-align: center;\">Test <em>test</em> test <span style=\"color: #71f10d;\">test</span></p>";
    post.setDescription(description);
    category = "test";
    post.addCategory(category);
    status = "publish";
    post.setPostStatus(status);
    tags = "test, html, formatting, richtext";
    post.setTags(tags);
    service->newPost(post);
    return app.exec();
}
