set(namespace d5c54b4a-2500-47f2-87a3-c35a5ca5abb6)

string(UUID res NAMESPACE ${namespace} NAME a TYPE MD5)
message("${res}") # 输出：97767c4e-ad2d-3ec2-a886-dff6f9fbeb86

string(UUID res NAMESPACE ${namespace} NAME b TYPE SHA1 UPPER)
message("${res}") # 输出：0460F7B4-BE40-5B00-B09A-C990B316B752