import boto3

client = boto3.client('ec2', region_name='eu-north-1')

instance_tags = client.describe_instances()

ids= [instance['InstanceId']
    for reservation in instance_tags['Reservations']
    for instance in reservation['Instances']]

response = client.stop_instances(
        InstanceIds=ids
)
print("Stopped now", response)